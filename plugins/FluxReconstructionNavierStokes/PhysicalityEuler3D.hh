#ifndef COOLFluiD_FluxReconstructionMethod_PhysicalityEuler3D_hh
#define COOLFluiD_FluxReconstructionMethod_PhysicalityEuler3D_hh

//////////////////////////////////////////////////////////////////////////////

#include "Framework/DataSocketSink.hh"

#include "FluxReconstructionMethod/FluxReconstructionSolverData.hh"

#include "FluxReconstructionMethod/BasePhysicality.hh"

#include "Framework/MultiScalarTerm.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {
  
  namespace Physics {
    namespace NavierStokes {
      class Euler3DVarSet;
    }
  }

  namespace FluxReconstructionMethod {

//////////////////////////////////////////////////////////////////////////////

/**
 * This class represent a command that checks and enforces the physicality of 
 * an Euler/NS 3D state, particularly the positivity of the 
 * pressure/density/temperature
 *
 * @author Ray Vandenhoeck
 *
 */
class PhysicalityEuler3D : public BasePhysicality {
public:

  /**
   * Constructor.
   */
  explicit PhysicalityEuler3D(const std::string& name);

  /**
   * Destructor.
   */
  virtual ~PhysicalityEuler3D();

  /**
   * Defines the Config Option's of this class
   * @param options a OptionList where to add the Option's
   */
  static void defineConfigOptions(Config::OptionList& options);

  /**
   * Setup private data and data of the aggregated classes
   * in this command before processing phase
   */
  virtual void setup();

  /**
   * Unsetup private data
   */
  virtual void unsetup();

  /**
   * Configures the command.
   */
  virtual void configure ( Config::ConfigArgs& args );

protected: // functions

  /**
   * apply pressure possitivity check
   */
  virtual void enforcePhysicality();
  
  /**
   * Check if the states are physical
   */
  virtual bool checkPhysicality();

protected: // data

  /// minimum allowable value for density
  CFreal m_minDensity;

  /// minimum allowable value for pressure
  CFreal m_minPressure;
  
  /// minimum allowable value for temperature
  CFreal m_minTemperature;
  
  /// minimum allowable value for gamma
  CFreal m_minGamma;
  
  /// maximum allowable value for gamma
  CFreal m_maxGamma;
  
  /// boolean telling wether to also check the internal solution for physicality
  bool m_checkInternal;
  
  /// boolean to tell whether the complete state is limited or a single variable
  bool m_limCompleteState;
  
  /// boolean telling whether to use the experimental limiter
  bool m_expLim;
  
  /// boolean telling whether to clip gamma
  bool m_clipGamma;
  
  /// physical model (in conservative variables)
  Common::SafePtr<Physics::NavierStokes::Euler3DVarSet> m_eulerVarSet;
  
  /// physical model  MS
  Common::SafePtr< Framework::MultiScalarTerm< Physics::NavierStokes::EulerTerm > > m_eulerVarSetMS;

  /// heat capacity ratio minus one
  CFreal m_gammaMinusOne;
  
  /// variable for physical data of sol
  RealVector m_solPhysData;
  
  /// cell averaged state
  RealVector m_cellAvgState;
  
  /// coefficients for the computation of the cell averaged solution
  Common::SafePtr< RealVector > m_cellAvgSolCoefs;
  
  /// number of species
  CFuint m_nbSpecies;

}; // class PhysicalityEuler3D

//////////////////////////////////////////////////////////////////////////////

  } // namespace FluxReconstructionMethod

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_FluxReconstructionMethod_PhysicalityEuler3D_hh
