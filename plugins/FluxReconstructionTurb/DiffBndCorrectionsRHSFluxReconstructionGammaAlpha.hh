#ifndef COOLFluiD_FluxReconstructionMethod_DiffBndCorrectionsRHSFluxReconstructionGammaAlpha_hh
#define COOLFluiD_FluxReconstructionMethod_DiffBndCorrectionsRHSFluxReconstructionGammaAlpha_hh

//////////////////////////////////////////////////////////////////////////////

#include "FluxReconstructionTurb/DiffBndCorrectionsRHSFluxReconstructionTurb.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

    namespace FluxReconstructionMethod {

//////////////////////////////////////////////////////////////////////////////

  /**
   * This class represents a command that computes contribution of the boundary faces for the
   * Flux Reconstruction schemes for diffusive terms to the RHS for implicit schemes for GammaAlpha
   *
   * @author Ray Vandenhoeck
   *
   */
class DiffBndCorrectionsRHSFluxReconstructionGammaAlpha : public DiffBndCorrectionsRHSFluxReconstructionTurb {

public:

  /**
   * Constructor
   */
  DiffBndCorrectionsRHSFluxReconstructionGammaAlpha(const std::string& name);

  /**
   * Default destructor
   */
  virtual ~DiffBndCorrectionsRHSFluxReconstructionGammaAlpha();
  
  /**
   * Set up private data and data of the aggregated classes
   * in this command before processing phase
   */
  virtual void setup();
  
  /**
   * unset up private data and data of the aggregated classes
   * in this command before processing phase
   */
  virtual void unsetup();
  
  /// compute the states, gradients and ghost states, gradients in the flx pnts
  virtual void computeFlxPntStates();

protected: // functions

  
protected: // data

    
}; // end of class DiffBndCorrectionsRHSFluxReconstructionGammaAlpha

//////////////////////////////////////////////////////////////////////////////

 } // namespace FluxReconstructionMethod

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_FluxReconstructionMethod_DiffBndCorrectionsRHSFluxReconstructionGammaAlpha_hh
