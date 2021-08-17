// GenieWeightCalc.cxx
//
// Handles event weights for GENIE systematics studies
//
// Updated by Marco Del Tutto on Feb 18 2017
//
// Ported from uboonecode to larsim on Feb 14 2017
//   by Marco Del Tutto <marco.deltutto@physics.ox.ac.uk>
//
// Heavily rewritten on Dec 9 2019
//   by Steven Gardiner <gardiner@fnal.gov>
// Updated for merge into larsim develop branch on Feb 22 2021 by Steven Gardiner
//
// Ported from larsim on Aug. 2021, 
//	by Keng Lin
//-----------------------------------------------------------

// Standard library includes
#include <map>
#include <memory>
#include <set>

// Framework includes
#include "art/Framework/Principal/Event.h"
#include "cetlib_except/exception.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include "sbncode/SBNEventWeight/Base/WeightCalc.h"
#include "sbncode/SBNEventWeight/Base/WeightCalcCreator.h"

//#include "CLHEP/Random/RandGaussQ.h"

#include "nugen/EventGeneratorBase/GENIE/GENIE2ART.h"

//#include "nugen/NuReweight/art/NuReweight.h"
#include "nusimdata/SimulationBase/MCFlux.h"
#include "nusimdata/SimulationBase/MCTruth.h"
#include "nusimdata/SimulationBase/GTruth.h"

//GENIE includes
#include "GENIE/Framework/Conventions/KineVar.h"
#include "GENIE/Framework/EventGen/EventRecord.h"
#include "GENIE/Framework/Interaction/Interaction.h"
#include "GENIE/Framework/Interaction/Kinematics.h"
#include "GENIE/Framework/Messenger/Messenger.h"
#include "GENIE/Framework/Utils/AppInit.h"

#include "GENIE/RwFramework/GSystSet.h"
#include "GENIE/RwFramework/GSyst.h"
#include "GENIE/RwFramework/GReWeight.h"
#include "GENIE/RwCalculators/GReWeightNuXSecNCEL.h"
#include "GENIE/RwCalculators/GReWeightNuXSecCCQE.h"
#include "GENIE/RwCalculators/GReWeightNuXSecCCRES.h"
#include "GENIE/RwCalculators/GReWeightNuXSecCOH.h"
#include "GENIE/RwCalculators/GReWeightNonResonanceBkg.h"
#include "GENIE/RwCalculators/GReWeightFGM.h"
#include "GENIE/RwCalculators/GReWeightDISNuclMod.h"
#include "GENIE/RwCalculators/GReWeightResonanceDecay.h"
#include "GENIE/RwCalculators/GReWeightFZone.h"
#include "GENIE/RwCalculators/GReWeightINuke.h"
#include "GENIE/RwCalculators/GReWeightAGKY.h"
#include "GENIE/RwCalculators/GReWeightNuXSecCCQEaxial.h"
#include "GENIE/RwCalculators/GReWeightNuXSecCCQEvec.h"
#include "GENIE/RwCalculators/GReWeightNuXSecNCRES.h"
#include "GENIE/RwCalculators/GReWeightNuXSecDIS.h"
#include "GENIE/RwCalculators/GReWeightINukeParams.h"
#include "GENIE/RwCalculators/GReWeightNuXSecNC.h"
#include "GENIE/RwCalculators/GReWeightXSecEmpiricalMEC.h"

////CHECK, need GENIE from ub
//// New weight calculator in GENIE v3.0.4 MicroBooNE patch 01
//#include "GENIE/RwCalculators/GReWeightXSecMEC.h"
//
//// New weight calculators in GENIE v3.0.4 MicroBooNE patch 02
//#include "GENIE/RwCalculators/GReWeightDeltaradAngle.h"
//#include "GENIE/RwCalculators/GReWeightNuXSecCOHuB.h"
//#include "GENIE/RwCalculators/GReWeightRESBugFix.h"


namespace sbn {
namespace {//Helper functions are defined in this block

  // These GENIE knobs are listed in the GSyst_t enum type but are not actually implemented.
  // They will be skipped and a warning message will be printed.
  // Last updated 9 Dec 2019 by S. Gardiner
  std::set< genie::rew::GSyst_t > UNIMPLEMENTED_GENIE_KNOBS = {
    kXSecTwkDial_RnubarnuCC,  // tweak the ratio of \sigma(\bar\nu CC) / \sigma(\nu CC)
    kXSecTwkDial_NormCCQEenu, // tweak CCQE normalization (maintains dependence on neutrino energy)
    kXSecTwkDial_NormDISCC,   // tweak the inclusive DIS CC normalization
    kXSecTwkDial_DISNuclMod   // unclear intent, does anyone else know? - S. Gardiner
  };

  // Some GENIE weight calculators can work with sets of knobs that should not be used simultaneously.
  // For instance, the CCQE weight calculator can vary parameters for the dipole axial form factor model
  // (the axial mass Ma) or for the z-expansion model, but using both together is invalid. The map below
  // is used to check that all of the requested knobs from the FHiCL input are compatible with each
  // other. Assuming they pass this check, the code will then configure the weight calculators to use
  // the correct "basis" of reweighting knobs as appropriate.

  // Outer keys are names of GENIE weight calculators that use sets of incompatible knobs. The names
  // need to match those used in GenieWeightCalc::SetupWeightCalculators(), specifically in the
  // calls to genie::rew::GReWeight::AdoptWeightCalc().
  // Inner keys are integer codes used to represent (and configure) each of the mutually exclusive
  // modes (i.e., to select one of the sets of incompatible knobs to use for the weight calculation).
  // Values are GSyst_t knob labels that belong to the given mode.
  std::map< std::string, std::map<int, std::set<genie::rew::GSyst_t> > > INCOMPATIBLE_GENIE_KNOBS = {
    // CCQE (genie::rew::GReWeightNuXSecCCQE)
    { "xsec_ccqe", {
      { genie::rew::GReWeightNuXSecCCQE::kModeNormAndMaShape,
        {
          // Norm + shape
          kXSecTwkDial_NormCCQE,    // tweak CCQE normalization (energy independent)
          kXSecTwkDial_MaCCQEshape, // tweak Ma CCQE, affects dsigma(CCQE)/dQ2 in shape only (normalized to constant integral)
          kXSecTwkDial_E0CCQEshape  // tweak E0 CCQE RunningMA, affects dsigma(CCQE)/dQ2 in shape only (normalized to constant integral)
        }
      },
      { genie::rew::GReWeightNuXSecCCQE::kModeMa,
        {
          // Ma
          kXSecTwkDial_MaCCQE, // tweak Ma CCQE, affects dsigma(CCQE)/dQ2 both in shape and normalization
          kXSecTwkDial_E0CCQE, // tweak E0 CCQE RunningMA, affects dsigma(CCQE)/dQ2 both in shape and normalization
        }
      },
      { genie::rew::GReWeightNuXSecCCQE::kModeZExp,
        {
          // Z-expansion
          kXSecTwkDial_ZNormCCQE,  // tweak Z-expansion CCQE normalization (energy independent)
          kXSecTwkDial_ZExpA1CCQE, // tweak Z-expansion coefficient 1, affects dsigma(CCQE)/dQ2 both in shape and normalization
          kXSecTwkDial_ZExpA2CCQE, // tweak Z-expansion coefficient 2, affects dsigma(CCQE)/dQ2 both in shape and normalization
          kXSecTwkDial_ZExpA3CCQE, // tweak Z-expansion coefficient 3, affects dsigma(CCQE)/dQ2 both in shape and normalization
          kXSecTwkDial_ZExpA4CCQE  // tweak Z-expansion coefficient 4, affects dsigma(CCQE)/dQ2 both in shape and normalization
        }
      },
    } },

    // CCRES (genie::rew::GReWeightNuXSecCCRES)
    { "xsec_ccres", {
      { genie::rew::GReWeightNuXSecCCRES::kModeNormAndMaMvShape,
        {
          // Norm + shape
          kXSecTwkDial_NormCCRES,    /// tweak CCRES normalization
          kXSecTwkDial_MaCCRESshape, /// tweak Ma CCRES, affects d2sigma(CCRES)/dWdQ2 in shape only (normalized to constant integral)
          kXSecTwkDial_MvCCRESshape  /// tweak Mv CCRES, affects d2sigma(CCRES)/dWdQ2 in shape only (normalized to constant integral)
        }
      },
      { genie::rew::GReWeightNuXSecCCRES::kModeMaMv,
        {
          // Ma + Mv
          kXSecTwkDial_MaCCRES, // tweak Ma CCRES, affects d2sigma(CCRES)/dWdQ2 both in shape and normalization
          kXSecTwkDial_MvCCRES  // tweak Mv CCRES, affects d2sigma(CCRES)/dWdQ2 both in shape and normalization
        }
      }
    } },

    // NCRES (genie::rew::GReWeightNuXSecNCRES)
    { "xsec_ncres", {
      { genie::rew::GReWeightNuXSecNCRES::kModeNormAndMaMvShape,
        {
          // Norm + shape
          kXSecTwkDial_NormNCRES,    /// tweak NCRES normalization
          kXSecTwkDial_MaNCRESshape, /// tweak Ma NCRES, affects d2sigma(NCRES)/dWdQ2 in shape only (normalized to constant integral)
          kXSecTwkDial_MvNCRESshape  /// tweak Mv NCRES, affects d2sigma(NCRES)/dWdQ2 in shape only (normalized to constant integral)
        }
      },
      { genie::rew::GReWeightNuXSecNCRES::kModeMaMv,
        {
          // Ma + Mv
          kXSecTwkDial_MaNCRES, // tweak Ma NCRES, affects d2sigma(NCRES)/dWdQ2 both in shape and normalization
          kXSecTwkDial_MvNCRES  // tweak Mv NCRES, affects d2sigma(NCRES)/dWdQ2 both in shape and normalization
        }
      }
    } },

    // DIS (genie::rew::GReWeightNuXSecDIS)
    { "xsec_dis", {
      { genie::rew::GReWeightNuXSecDIS::kModeABCV12u,
        {
          kXSecTwkDial_AhtBY,  // tweak the Bodek-Yang model parameter A_{ht} - incl. both shape and normalization effect
          kXSecTwkDial_BhtBY,  // tweak the Bodek-Yang model parameter B_{ht} - incl. both shape and normalization effect
          kXSecTwkDial_CV1uBY, // tweak the Bodek-Yang model parameter CV1u - incl. both shape and normalization effect
          kXSecTwkDial_CV2uBY  // tweak the Bodek-Yang model parameter CV2u - incl. both shape and normalization effect
        }
      },
      { genie::rew::GReWeightNuXSecDIS::kModeABCV12uShape,
        {
          kXSecTwkDial_AhtBYshape,  // tweak the Bodek-Yang model parameter A_{ht} - shape only effect to d2sigma(DIS)/dxdy
          kXSecTwkDial_BhtBYshape,  // tweak the Bodek-Yang model parameter B_{ht} - shape only effect to d2sigma(DIS)/dxdy
          kXSecTwkDial_CV1uBYshape, // tweak the Bodek-Yang model parameter CV1u - shape only effect to d2sigma(DIS)/dxdy
          kXSecTwkDial_CV2uBYshape  // tweak the Bodek-Yang model parameter CV2u - shape only effect to d2sigma(DIS)/dxdy
        }
      }
    } }
  };


  // Helper function that checks whether a string storing a GENIE knob name is
  // valid. Also stores the corresponding GSyst_t enum value for the knob.
  // This grab the knob by <string> name;
  bool valid_knob_name( const std::string& knob_name, genie::rew::GSyst_t& knob ) {
    knob = genie::rew::GSyst::FromString( knob_name );
    if ( knob != kNullSystematic && knob != kNTwkDials ) {
      if ( UNIMPLEMENTED_GENIE_KNOBS.count(knob) ) {
        MF_LOG_WARNING("GENIEWeightCalc") << "Ignoring unimplemented GENIE"
          << " knob " << knob_name;
        return false;
      }
    }
    else {
      throw cet::exception(__PRETTY_FUNCTION__) << "Encountered unrecognized"
        "GENIE knob \"" << knob_name << '\"';
      return false;
    }
    return true;
  }


  // Set of FHiCL weight calculator labels for which the tuned CV will be
  // ignored. If the name of the weight calculator doesn't appear in this set,
  // then variation weights will be thrown around the tuned CV.
  std::set< std::string > CALC_NAMES_THAT_IGNORE_TUNED_CV = { "RootinoFix" };

} // anonymous namespace


  namespace evwgh {

class GenieWeightCalc : public WeightCalc {
public:
  GenieWeightCalc() : WeightCalc() {}

	//CHECK
  void Configure(fhicl::ParameterSet const& pset,
                 CLHEP::HepRandomEngine& engine) override;

  std::vector<float> GetWeight(art::Event& e, size_t inu) override;

private:
//  std::vector<rwgt::NuReweight> rwVector;
  //CHECK replace:
  std::vector< genie::rew::GReWeight > reweightVector;

  std::string fGenieModuleLabel;
  std::string fTuneName;

  //CHECK add these
  std::map< std::string, int > CheckForIncompatibleSystematics(
        const std::vector<genie::rew::GSyst_t>& knob_vec);

	//CHECK
  void SetupWeightCalculators(genie::rew::GReWeight& rw,
        const std::map<std::string, int>& modes_to_use);

 
  bool fQuietMode;//quiet mode

  DECLARE_WEIGHTCALC(GenieWeightCalc)
};


void GenieWeightCalc::Configure(fhicl::ParameterSet const& p,
		CLHEP::HepRandomEngine& engine) {
	// Check add some messengers

	// Global config
	fGenieModuleLabel = p.get<std::string>("genie_module_label");

	const fhicl::ParameterSet& param_CVs = p.get<fhicl::ParameterSet>(
			"genie_central_values", fhicl::ParameterSet() );
	std::vector< std::string > CV_knob_names = param_CVs.get_all_keys();

	std::map< genie::rew::GSyst_t, double > gsyst_to_cv_map;
	genie::rew::GSyst_t temp_knob;

	// Check add some messengers

	// Calculator config
	const fhicl::ParameterSet& pset = p.get<fhicl::ParameterSet>(GetName());
	auto const& pars = pset.get<std::vector<std::string> >("parameter_list");
	auto const& parsigmas = pset.get<std::vector<float> >("parameter_sigma");

	auto const par_mins = pset.get< std::vector<float> >( "parameter_min");
	auto const par_maxes = pset.get< std::vector<float> >( "parameter_max");


	if (pars.size() != parsigmas.size()) {
		throw cet::exception(__PRETTY_FUNCTION__) << GetName() << ": "
			<< "parameter_list and parameter_sigma length mismatch."
			<< std::endl;
	}

	std::string mode = pset.get<std::string>("mode");

	//CHECK, add a check on sigmas_ok

	// Convert the list of GENIE knob names from the input FHiCL configuration
	// into a vector of genie::rew::GSyst_t labels
	std::vector< genie::rew::GSyst_t > knobs_to_use;
	for ( const auto& knob_name : pars ) {
		if ( valid_knob_name(knob_name, temp_knob) ) knobs_to_use.push_back( temp_knob );
	}

	//check if all_knobs_vec are good
    std::vector< genie::rew::GSyst_t > all_knobs_vec = knobs_to_use;
    for ( const auto& pair : gsyst_to_cv_map ) {
      genie::rew::GSyst_t cv_knob = pair.first;
      auto begin = all_knobs_vec.cbegin();
      auto end = all_knobs_vec.cend();
      if ( !std::count(begin, end, cv_knob) ) all_knobs_vec.push_back( cv_knob );
    }
    std::map< std::string, int >
      modes_to_use = this->CheckForIncompatibleSystematics( all_knobs_vec );

	int num_universes = 1; //for "central_value" or "default" mode

	 if ( mode.find("pm1sigma") != std::string::npos
      || mode.find("minmax") != std::string::npos )
    {
      num_universes = 2;
    }
    else if ( mode.find("multisim") != std::string::npos ) {
      num_universes = pset.get<int>( "number_of_multisims", 1 );

      // Since we're in multisim mode, force retrieval of the random
      // number seed. If it wasn't set, this will trigger an exception.
      // We want this check because otherwise the multisim universes
      // will not be easily reproducible.
//      int dummy_seed = pset.get<int>( "random_seed" );
//      MF_LOG_INFO("GENIEWeightCalc") << "GENIE weight calculator "
//        << this->GetName() << " will generate " << num_universes
//        << " multisim universes";// with random seed " << dummy_seed;
    }

	// Set up parameters
	fParameterSet.Configure(GetFullName(), mode, num_universes);

	for (size_t i=0; i<pars.size(); i++) {
		//CHECK, only add the compatible knobs;
		fParameterSet.AddParameter(pars[i], parsigmas[i]);
		//AddParameter(name, width, mean=0, covIndex=0);
		//Create object EventWeightParameter p(name, mean, width, covIndex)
		//
		//`it.second` from fParameterSet.fParameterMap 
		//		is a vector<float> defined by the following;
		//"multisim" gives: CLHEP::RandGaussQ::shoot(&engine, p.fMean, p.fWidth)
		//"kPMNSigma" gives: p.fMean + p.fWidth & p.fMean + p.fWidth
		//(CHECK), update kPMNSigma
		//"kFixed" gives: p.fMean + p.fWidth
		//"No other modes"
		//
		//CHECK, need to update sbnobj for more modes?
		//sbnobj: mulsitims/PMNSigma/Fixed (include 3 cases); default, exit;
		//							 (width,mean)=(0,\pm1)/(0,0)/(0,sigma);
		//Larsim: multisim/pm1sigma/minmax/central_value; default, exact sigma;
		//multisim gives: sigmas* CLHEP::RandGaussQ::shoot(&engine, 0., 1.); [DIFFERENT] CHECK
	}

	fParameterSet.Sample(engine);


	//loop over parameters;
	for (auto const& it : fParameterSet.fParameterMap) {//member of std::map<EventWeightParameter, std::vector<float> >
	//(see line 41 of sbnobj/Common/SBNEventWeight/EventWeightParameterSet.h)
		std::string name = it.first.fName;
		std::cout << GetFullName() << ": Setting up " << name << std::endl;
		// Set up reweighters
		//rwVector.resize(fParameterSet.fNuniverses);
		reweightVector.resize( num_universes );// Reconfigure this later in this function.

		// Set up the weight calculators for each universe
		for ( auto& rwght : reweightVector ){ this->SetupWeightCalculators( rwght, modes_to_use );}
		// Set up GENIE with the currently active tune
		// CHCEK, not used?
		//	evgb::SetEventGeneratorListAndTune();
		//	fTuneName = evgb::ExpandEnvVar("${GENIE_XSEC_TUNE}");


		//Assign knob with new values based on variation
		//loop over universes
		for ( size_t u = 0; u < reweightVector.size(); ++u ) {

			auto& rwght = reweightVector.at( u );
			genie::rew::GSystSet& syst = rwght.Systematics();

//			for ( unsigned int k = 0; k < knobs_to_use.size(); ++k ) {
				genie::rew::GSyst_t knob; 
				valid_knob_name(name, knob);//= valid_knob_nameknobs_to_use.at( k );
				//genie::rew::GSyst_t knob = //knobs_to_use.at( k );

				double twk_dial_value = it.second[u];//reweightingSigmas.at( k ).at( u );//kth knob, uth universe
				syst.Set( knob, twk_dial_value );

				if ( !fQuietMode ) {
					MF_LOG_INFO("GENIEWeightCalc") << "In universe #" << u << ", knob name" << name // << k
						<< " (" << genie::rew::GSyst::AsString( knob ) << ") was set to"
						<< " the value " << twk_dial_value;
				}
//			} // loop over tweaked knobs

			rwght.Reconfigure();
			rwght.Print();
		}//next universe
	}//next parameter

//	for (auto const& it : fParameterSet.fParameterMap) {
//		std::string name = it.first.fName;
//		std::cout << GetFullName() << ": Setting up " << name << std::endl;
//
//		for (size_t i=0; i<fParameterSet.fNuniverses; i++) {
//			rwgt::NuReweight& rw = rwVector[i];
//
//			if (name == "IntraNukePIpi")
//				rw.ReweightIntraNuke(rwgt::fReweightFrPiProd_pi, it.second[i]);
//			// Unknown
//			else {
//				throw cet::exception(__PRETTY_FUNCTION__) << GetName() << ": "
//					<< "Unknown GENIE parameter " << name << std::endl;
//			}
//		}
//	}

	// Configure reweight drivers
//	for (auto& rw : rwVector) {
//		rw.Configure();
//	}
}

//Keng:
//copied from larsim's GetWeight()
//2d weights --> 1d weights; no major modifications.
std::vector<float> GenieWeightCalc::GetWeight(art::Event& e, size_t inu) {
    // Get the MC generator information out of the event
    // These are both handles to MC information.
    art::Handle< std::vector<simb::MCTruth> > mcTruthHandle;
    art::Handle< std::vector<simb::GTruth> > gTruthHandle;

    // Actually go and get the stuff
    e.getByLabel( fGenieModuleLabel, mcTruthHandle );
    e.getByLabel( fGenieModuleLabel, gTruthHandle );

    std::vector< art::Ptr<simb::MCTruth> > mclist;
    art::fill_ptr_vector( mclist, mcTruthHandle );

    std::vector< art::Ptr<simb::GTruth > > glist;
    art::fill_ptr_vector( glist, gTruthHandle );

//    size_t num_neutrinos = mclist.size();
    size_t num_knobs = reweightVector.size();

    // Calculate weight(s) here
    std::vector< float > weights( num_knobs );
//    std::vector< std::vector<double> > weights( num_neutrinos );

      // Convert the MCTruth and GTruth objects from the event
      // back into the original genie::EventRecord needed to
      // compute the weights
      std::unique_ptr< genie::EventRecord >
        genie_event( evgb::RetrieveGHEP(*mclist[inu], *glist[inu]) );

      // Set the final lepton kinetic energy and scattering cosine
      // in the owned GENIE kinematics object. This is done during
      // event generation but is not reproduced by evgb::RetrieveGHEP().
      // Several new CCMEC weight calculators developed for MicroBooNE
      // expect the variables to be set in this way (so that differential
      // cross sections can be recomputed). Failing to set them results
      // in inf and NaN weights.
      // TODO: maybe update evgb::RetrieveGHEP to handle this instead.
      genie::Interaction* interaction = genie_event->Summary();
      genie::Kinematics* kine_ptr = interaction->KinePtr();

      // Final lepton mass
      double ml = interaction->FSPrimLepton()->Mass();
      // Final lepton 4-momentum
      const TLorentzVector& p4l = kine_ptr->FSLeptonP4();
      // Final lepton kinetic energy
      double Tl = p4l.E() - ml;
      // Final lepton scattering cosine
      double ctl = p4l.CosTheta();

      kine_ptr->SetKV( kKVTl, Tl );
      kine_ptr->SetKV( kKVctl, ctl );

      // All right, the event record is fully ready. Now ask the GReWeight
      // objects to compute the weights.
      for (size_t k = 0u; k < num_knobs; ++k ) {
        weights[k] = reweightVector.at( k ).CalcWeight( *genie_event );
      }
    
    return weights;


}


//CHECK, this can potentially be simplified;
std::map< std::string, int > GenieWeightCalc::CheckForIncompatibleSystematics(
		const std::vector<genie::rew::GSyst_t>& knob_vec){
    std::map< std::string, int > modes_to_use;

    for ( const auto& knob : knob_vec ) {
      for ( const auto& pair1 : INCOMPATIBLE_GENIE_KNOBS ) {
        std::string calc_name = pair1.first;
        const auto& mode_map = pair1.second;
        for ( const auto& pair2 : mode_map ) {
          int mode = pair2.first;//<int> code of the variable
          std::set<genie::rew::GSyst_t> knob_set = pair2.second;//incomp. knobs

          if ( knob_set.count(knob) ) {//<string> leads to incomp. knobs
            auto search = modes_to_use.find( calc_name );
            if ( search != modes_to_use.end() ) {//found a incomp. knob's name
              if ( search->second != mode ) {//if the knob is not connected to the variable?
                auto knob_str = genie::rew::GSyst::AsString( knob );
                throw cet::exception(__PRETTY_FUNCTION__) << this->GetName()
                  << ": the GENIE knob " << knob_str << " is incompatible"
                  << " with others that are already configured";
              }
            }
            else modes_to_use[ calc_name ] = mode;
          }
        }
      }
    }

    return modes_to_use;
  }


void GenieWeightCalc::SetupWeightCalculators(genie::rew::GReWeight& rw,
		const std::map<std::string, int>& modes_to_use){
		
		}



REGISTER_WEIGHTCALC(GenieWeightCalc)

  }  // namespace evwgh
}  // namespace sbn



