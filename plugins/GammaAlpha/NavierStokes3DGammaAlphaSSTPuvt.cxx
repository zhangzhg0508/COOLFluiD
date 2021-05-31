#include "GammaAlpha.hh"
#include "NavierStokes3DGammaAlphaSSTPuvt.hh"
#include "Environment/ObjectProvider.hh"
#include "Framework/MeshData.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;
using namespace COOLFluiD::Common;
using namespace COOLFluiD::Physics::NavierStokes;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {

    namespace GammaAlpha {

//////////////////////////////////////////////////////////////////////////////

Environment::ObjectProvider<NavierStokes3DGammaAlphaSSTPuvt, DiffusiveVarSet,
	       GammaAlphaModule, 2>
ns3DGammaAlphaSSTPuvtProvider("NavierStokes3DGammaAlphaSSTPvt");

//////////////////////////////////////////////////////////////////////////////

NavierStokes3DGammaAlphaSSTPuvt::NavierStokes3DGammaAlphaSSTPuvt
(const std::string& name, SafePtr<PhysicalModelImpl> model) :
  NavierStokes3DGammaAlphaBSLPuvt(name, model)
{
}

//////////////////////////////////////////////////////////////////////////////

NavierStokes3DGammaAlphaSSTPuvt::~NavierStokes3DGammaAlphaSSTPuvt()
{
}

//////////////////////////////////////////////////////////////////////////////

void NavierStokes3DGammaAlphaSSTPuvt::setModelCoefficients()
{

  NavierStokes3DGammaAlphaPuvt::setModelCoefficients();

  //Modified k-omega coeficients for SST
  _sigmaK1 = 0.85;
 // _sigmaK2 = 1.0;
 // _sigmaOmega2 = 0.856;
 // _beta2 = 0.0828;
  
 // Menter SST model from 2003  
 // _gamma1= 5/9;
 // _gamma2= 0.44;
}

//////////////////////////////////////////////////////////////////////////////

CFreal NavierStokes3DGammaAlphaSSTPuvt::getTurbDynViscosityFromGradientVars(const RealVector& state, const vector<RealVector*>& gradients)
{

  cf_assert(_wallDistance >= 0.);
  //cf_assert(gradients.size() > 0);

  CFreal mut = 0.;
  if((_wallDistance > 0.) && (gradients.size() > 0))
  {
    const CFreal a1 = 0.31;

    const CFreal rho = std::max(0., getDensity(state));
    const CFreal K = std::max(state[5],0.0);
    const CFreal Omega = std::exp(state[6]);
    
    //const CFreal vorticity = fabs((*(gradients[2]))[XX] - (*(gradients[1]))[YY]);
    const CFreal gradU_X = (*(gradients[1]))[XX];
    const CFreal gradU_Y = (*(gradients[1]))[YY];
    const CFreal gradU_Z = (*(gradients[1]))[ZZ];
    const CFreal gradV_X = (*(gradients[2]))[XX];
    const CFreal gradV_Y = (*(gradients[2]))[YY];
    const CFreal gradV_Z = (*(gradients[2]))[ZZ];
    const CFreal gradW_X = (*(gradients[3]))[XX];
    const CFreal gradW_Y = (*(gradients[3]))[YY];
    const CFreal gradW_Z = (*(gradients[3]))[ZZ];
    
    const CFreal gradSumXY = (gradU_Y + gradV_X);
    const CFreal gradSumXZ = (gradU_Z + gradW_X);
    const CFreal gradSumYZ = (gradW_Y + gradV_Z);
      
    const CFreal strain = std::sqrt(2.*(gradU_X*gradU_X + gradV_Y*gradV_Y + gradW_Z*gradW_Z) + gradSumXY*gradSumXY + gradSumXZ*gradSumXZ + gradSumYZ*gradSumYZ);

    const CFreal mu = getLaminarDynViscosityFromGradientVars(state);
    const CFreal avGa = std::min(std::max(state[7],0.01),0.99);
    //const CFreal avGa = std::min(std::max(state[6],0.01),1.0);

    ///@todo here there should be an adimensionalization coef
    const CFreal arg2_1 = 2. * sqrt(K) / (0.09 * Omega * _wallDistance);
    const CFreal arg2_2 = (500. * mu) / (rho * _wallDistance * _wallDistance * Omega);
    const CFreal arg2 = std::max(arg2_1,arg2_2);

    const CFreal F2 = tanh(arg2*arg2);

    mut = (a1 * rho * K )/ std::max(a1*Omega , strain*F2);
    
    // compute effective eddy viscosity
    const CFreal cmut1 = 0.5;//0.68;//
    const CFreal cmut2 = 0.25;
    const CFreal cmut3 = 0.1;
    mut *= (avGa+avGa*(1.0-avGa)*cmut1*(1.0+tanh((avGa-cmut2)/(cmut3))));
  }

  return mut;
}

//////////////////////////////////////////////////////////////////////////////

    } // namespace GammaAlpha

  } // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

