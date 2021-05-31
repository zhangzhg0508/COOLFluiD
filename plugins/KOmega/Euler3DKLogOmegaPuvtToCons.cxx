#include "KOmega.hh"
#include "Euler3DKLogOmegaPuvtToCons.hh"
#include "Framework/PhysicalModel.hh"
#include "Environment/ObjectProvider.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;
using namespace COOLFluiD::MathTools;
using namespace COOLFluiD::Physics::NavierStokes;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {

    namespace KOmega {

//////////////////////////////////////////////////////////////////////////////

Environment::ObjectProvider<Euler3DKLogOmegaPuvtToCons, VarSetTransformer, KOmegaModule, 1>
euler3DKLogOmegaPuvtToConsProvider("Euler3DKLogOmegaPvtToCons");

//////////////////////////////////////////////////////////////////////////////

Euler3DKLogOmegaPuvtToCons::Euler3DKLogOmegaPuvtToCons(Common::SafePtr<Framework::PhysicalModelImpl> model) :
  VarSetTransformer(model),
  _model(model->getConvectiveTerm().
	 d_castTo<EulerKLogOmegaTerm>())
{
}

//////////////////////////////////////////////////////////////////////////////

Euler3DKLogOmegaPuvtToCons::~Euler3DKLogOmegaPuvtToCons()
{
}

//////////////////////////////////////////////////////////////////////////////

void Euler3DKLogOmegaPuvtToCons::transform(const State& state, State& result)
{
  const CFreal R = _model->getR();
  const CFreal p = state[0];
  const CFreal u = state[1];
  const CFreal v = state[2];
  const CFreal w = state[3];
  const CFreal T = state[4];
  const CFreal K = state[5];
  const CFreal Omega = state[6];
  const CFreal rho = p/(R*T);
  const CFreal rhoV2 = rho*(u*u + v*v + w*w);

  result[0] = rho;
  result[1] = rho*u;
  result[2] = rho*v;
  result[3] = rho*w;
  result[4] = p/(_model->getGamma() - 1.) + 0.5*rhoV2;
  result[5] = rho*K;
  result[6] = rho*Omega;
}

//////////////////////////////////////////////////////////////////////////////

void Euler3DKLogOmegaPuvtToCons::transformFromRef(const RealVector& data, State& result)
{
  const CFreal rho = data[EulerKLogOmegaTerm::RHO];

  result[0] = rho;
  result[1] = rho*data[EulerKLogOmegaTerm::VX];
  result[2] = rho*data[EulerKLogOmegaTerm::VY];
  result[3] = rho*data[EulerKLogOmegaTerm::VZ];
  result[4] = rho*data[EulerKLogOmegaTerm::H] - data[EulerKLogOmegaTerm::P];

  const CFuint iK = _model->getFirstScalarVar(0);
  result[5] = rho*data[iK];
  result[6] = rho*data[iK+1];
}

//////////////////////////////////////////////////////////////////////////////

    } // namespace KOmega

  } // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
