#include "GammaAlpha.hh"
#include "Common/CFLog.hh"
#include "Euler2DGammaAlphaPuvt.hh"
#include "Common/NotImplementedException.hh"
#include "Environment/ObjectProvider.hh"
#include "NavierStokes/NSTurbTerm.hh"
#include "Framework/MeshData.hh"
#include "Framework/SubSystemStatus.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;
using namespace COOLFluiD::Common;
using namespace COOLFluiD::Physics::NavierStokes;
using namespace COOLFluiD::Physics::NavierStokes;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {

    namespace GammaAlpha {

//////////////////////////////////////////////////////////////////////////////

Environment::ObjectProvider<Euler2DGammaAlphaPuvt, ConvectiveVarSet, GammaAlphaModule, 1>
euler2DGammaAlphaPuvtProvider("Euler2DGammaAlphaPuvt");

//////////////////////////////////////////////////////////////////////////////

Euler2DGammaAlphaPuvt::Euler2DGammaAlphaPuvt(Common::SafePtr<BaseTerm> term) :
  MultiScalarVarSet<Euler2DPuvt>(term)
{
  const CFuint nbTurbEquations = getModel()->getNbScalarVars(0);

  vector<std::string> names(4 + nbTurbEquations);
  names[0] = "p";
  names[1] = "u";
  names[2] = "v";
  names[3] = "T";

  names[4] = "K";
  names[5] = "Omega";
  names[6] = "Gamma";
  names[7] = "Alpha";

  setVarNames(names);
}

//////////////////////////////////////////////////////////////////////////////

Euler2DGammaAlphaPuvt::~Euler2DGammaAlphaPuvt()
{
}

//////////////////////////////////////////////////////////////////////////////

void Euler2DGammaAlphaPuvt::computeEigenValuesVectors(RealMatrix& rightEv,
                                        RealMatrix& leftEv,
                                        RealVector& eValues,
                                        const RealVector& normal)
{
  throw Common::NotImplementedException (FromHere(),"Euler2DGammaAlphaPuvt::computeEigenValuesVectors()");
}

//////////////////////////////////////////////////////////////////////////////

CFuint Euler2DGammaAlphaPuvt::getBlockSeparator() const
{
  return Framework::PhysicalModelStack::getActive()->getNbEq();
}

//////////////////////////////////////////////////////////////////////////////

void Euler2DGammaAlphaPuvt::splitJacobian(RealMatrix& jacobPlus,
           RealMatrix& jacobMin,
           RealVector& eValues,
           const RealVector& normal)
{
  throw Common::NotImplementedException (FromHere(),"Euler2DGammaAlphaPuvt::splitJacobian()");
}

//////////////////////////////////////////////////////////////////////////////

void Euler2DGammaAlphaPuvt::computePhysicalData(const State& state,
					    RealVector& data)
{

  const CFreal p = state[0];
  const CFreal u = state[1];
  const CFreal v = state[2];
  const CFreal T = state[3];
  const CFreal K = state[4];
  const CFreal Omega = state[5];
  const CFreal Ga = state[6];
  const CFreal Alpha = state[7];

  const CFreal R = getModel()->getR();
  //The equaion of state is not  rho = p/(R*T) because k contributes to the conservation of total
  //energy
  const CFreal rho = p/(R*T);
  const CFreal overRho = 1./rho;
  const CFreal V2 = u*u + v*v;
  const CFreal gamma = getModel()->getGamma();
  const CFreal gammaMinus1 = gamma - 1.;
  const CFreal gammaDivGammaMinus1 = gamma/gammaMinus1;

  data[EulerTerm::VX] = u;
  data[EulerTerm::VY] = v;
  data[EulerTerm::RHO] = rho;
  data[EulerTerm::V] = sqrt(V2);
  data[EulerTerm::P] = p;
  data[EulerTerm::T] = T;
  data[EulerTerm::H] = gammaDivGammaMinus1*p*overRho + 0.5*V2;// + K;
  data[EulerTerm::E] = data[EulerTerm::H] - (p*overRho);

//  data[EulerTerm::A] = sqrt(gammaMinus1*(data[EulerTerm::H] - 0.5*V2) + (gammaMinus1*K);
  data[EulerTerm::A] = sqrt(gamma*data[EulerTerm::P]*overRho);
  data[EulerTerm::GAMMA] = gamma;

  const CFuint iK = getModel()->getFirstScalarVar(0);
  data[iK] = state[4];
  data[iK+1] = state[5];
  data[iK+2] = state[6];
  data[iK+3] = state[7];



}

//////////////////////////////////////////////////////////////////////////////

void Euler2DGammaAlphaPuvt::computeStateFromPhysicalData(const RealVector& data,
						State& state)
{
  const CFreal R = getModel()->getR();
  state[0] = data[EulerTerm::P];
  state[1] = data[EulerTerm::VX];
  state[2] = data[EulerTerm::VY];
  state[3] = data[EulerTerm::P]/(R*data[EulerTerm::RHO]);

  // Set the species
  const CFuint firstTurbVar = getModel()->getFirstScalarVar(0);
  const CFuint nbTurbVar = getModel()->getNbScalarVars(0);

  for (CFuint ie = 0; ie < nbTurbVar; ++ie){
    state[4 + ie] = data[firstTurbVar + ie];
  }

}

//////////////////////////////////////////////////////////////////////////////

CFreal Euler2DGammaAlphaPuvt::getSpeed(const State& state) const
{
  return sqrt(state[1]*state[1] + state[2]*state[2]);
}

//////////////////////////////////////////////////////////////////////////////

void Euler2DGammaAlphaPuvt::setDimensionalValues(const State& state,
                                          RealVector& result)
{
  const RealVector& refData = getModel()->getReferencePhysicalData();

  result[0] = state[0]*refData[EulerTerm::P];
  result[1] = state[1]*refData[EulerTerm::V];
  result[2] = state[2]*refData[EulerTerm::V];
  result[3] = state[3]*getModel()->getTempRef();

  const CFuint iK = getModel()->getFirstScalarVar(0);
  result[4] = state[4]*refData[iK];
  result[5] = state[5]*refData[iK+1];
  result[6] = state[6]*refData[iK+2];
  result[7] = state[7]*refData[iK+3];
}

//////////////////////////////////////////////////////////////////////////////

void Euler2DGammaAlphaPuvt::setAdimensionalValues(const State& state,
                                          RealVector& result)
{
  const RealVector& refData = getModel()->getReferencePhysicalData();

  result[0] = state[0]/refData[EulerTerm::P];
  result[1] = state[1]/refData[EulerTerm::V];
  result[2] = state[2]/refData[EulerTerm::V];
  result[3] = state[3]/(getModel()->getTempRef());

  const CFuint iK = getModel()->getFirstScalarVar(0);
  result[4] = state[4]/refData[iK];
  result[5] = state[5]/refData[iK+1];
  result[6] = state[6]/refData[iK+2];
  result[7] = state[7]/refData[iK+3];
}

//////////////////////////////////////////////////////////////////////////////

void Euler2DGammaAlphaPuvt::setDimensionalValuesPlusExtraValues
(const State& state, RealVector& result,
 RealVector& extra)
{
  const RealVector& refData = getModel()->getReferencePhysicalData();

  const CFreal pdim = state[0]*refData[EulerTerm::P];
  const CFreal udim = state[1]*refData[EulerTerm::V];
  const CFreal vdim = state[2]*refData[EulerTerm::V];
  const CFreal Tdim = state[3]*getModel()->getTempRef();

  result[0] = pdim;
  result[1] = udim;
  result[2] = vdim;
  result[3] = Tdim;

  const CFuint iK = getModel()->getFirstScalarVar(0);
  const CFreal Kdim = state[4]*refData[iK];
  const CFreal Omegadim = state[5]*refData[iK+1];
  const CFreal Gadim = state[6]*refData[iK+2];
  const CFreal alphadim = state[7]*refData[iK+3];
  result[4] = Kdim;
  result[5] = Omegadim;
  result[6] = Gadim;
  result[7] = alphadim;
  
  extra.resize(6);
  
  const CFreal Rdim = getModel()->getRdim();
  const CFreal rhoDim = pdim/(Rdim*Tdim);
  
  
  // TO BE ADDED MODIFOED mut is not correct
  SafePtr<NSTurbTerm> nsTurbTerm  =
    PhysicalModelStack::getActive()->getImplementor()->
    getDiffusiveTerm().d_castTo<NSTurbTerm>();
  
  const CFreal mu_dim = nsTurbTerm->getDynViscosityDim(pdim,Tdim) * refData[NSTurbTerm::MU];
  const CFreal mut_dim = rhoDim * Kdim / exp(Omegadim);
  
  extra[0] = mu_dim;
  extra[1] = mut_dim;
  extra[2] = mut_dim/mu_dim;
  
  const CFreal V2 = udim*udim + vdim*vdim;
  const CFreal V = std::sqrt(V2);
  // CFreal Tu=  100 * (std::sqrt(2*Kdim/3))/(V);
  CFreal Tu = min(max( 100 * (std::sqrt(2.0*max(Kdim,0.0)/3.0))/(V), 0.027),100.0);
  //const CFreal Tu       = 100 * (std::sqrt(2*Kdim/3))/(V);
  //const CFreal Tu1       = 100 * (std::sqrt(2*Kdim/3))/(std::max(V,1e-12));
  //const CFreal Tu1       = 100 * (std::sqrt(2*Kdim/3))/V; 
  //const CFreal Tu        = std::max(Tu1,0.027);
  //const CFreal Tu2       = std::min(Tu1,100.0);
  //const CFreal Tu        = std::max(Tu2,0.00031773);
  // const CFreal Tu        = std::max(Tu2,0.0);
  
  const CFreal overTu = 1.0/Tu;
  
  
  if (Tu<=1.3) {
    CFreal  Rethetat = (1173.51-589.428*Tu + 0.2196*overTu*overTu);
    extra[3] = Rethetat;
  }
  else {
    const CFreal lamco5   = Tu - 0.5658;
    const CFreal pwtu   = -0.671;
    CFreal Rethetat = 331.5*std::pow(lamco5,pwtu);
    extra[3] = Rethetat;
  }
  
  std::string namespaceName = Framework::MeshDataStack::getActive()->getPrimaryNamespace();
  //cout << namespaceName<< endl; 
  std::string dataHandleName = namespaceName + "_wallDistance";
  //std::string dataHandleName =  "WallDistance";
  // cout << dataHandleName << endl;
  bool exists = Framework::MeshDataStack::getActive()->getDataStorage()->checkData(dataHandleName);
  //bool exists = Framework::MeshDataStack::getActive()->getDataStorage()->checkData(dataHandleName);
  // cout << exists << endl;
  
  if(exists) {// this can only work when data are cell-centered otherwise you can have nodal stateID > actual array storage 
    DataHandle< double> wallDistance = MeshDataStack::getActive()->getDataStorage()->
      getData<CFreal>(dataHandleName);
    // const CFuint stateID = state.getLocalID();
    // if (stateID >= wallDistance.size()) {
    //  CFLog(INFO, "Euler2DGammaAlphaPuvt::setDimensionalValuesPlusExtraValues() => " << stateID << " >= " << wallDistance.size() << "\n");
    //}
    
    //Output the wall distance
    extra[4] = 0.; //wallDistance[stateID];
    
    // cout << " stateID   " << stateID <<  " wallDistance  " << wallDistance[stateID] << endl;
  }
  else{
    extra[4] = 0.;
  }
  
  extra[5] = Tu;
  
}

//////////////////////////////////////////////////////////////////////////////

vector<std::string> Euler2DGammaAlphaPuvt::getExtraVarNames() const
{

  vector<std::string> names(6);
  names[0] = "mu";
  names[1] = "muT";
  names[2] = "muT/mu";
  names[3] = "Rethetat";
  names[4] = "wallDistance";
  names[5] = "Tu";

  return names;

}

//////////////////////////////////////////////////////////////////////////////

void Euler2DGammaAlphaPuvt::setup()
{
  MultiScalarVarSet<Euler2DPuvt>::setup();
  
  // set the equation set data for each of the equation subsets
  // first equation subset
  Euler2DPuvt::getEqSetData().resize(1);
  Euler2DPuvt::getEqSetData()[0].setup(0,0,4);
  
  // second equation subset 
  MultiScalarVarSet<Euler2DPuvt>::getEqSetData().resize(1);
  MultiScalarVarSet<Euler2DPuvt>::getEqSetData()[0].setup
    (1,4,getModel()->getNbScalarVars(0));
}

//////////////////////////////////////////////////////////////////////////////

void Euler2DGammaAlphaPuvt::computePerturbedPhysicalData
(const Framework::State& currState,
 const RealVector& bData,
 RealVector& data,
 CFuint iVar)
{
  cf_assert(iVar < PhysicalModelStack::getActive()->getNbEq());
  
  const CFuint nbEqSS = PhysicalModelStack::getActive()->getEquationSubSysDescriptor().getTotalNbEqSS();
  
  if(nbEqSS == 1){
    computePhysicalData(currState, data);
  }
  
  if(nbEqSS == 2){
    if (iVar < 4) {  // u + du // v + dv // T + dT // p + dp
      computePhysicalData(currState, data);
      const CFuint iK = getModel()->getFirstScalarVar(0);
      data[iK] = bData[iK];
      data[iK+1] = bData[iK+1];
    }
    else { // k + dk   omega + dOmega
      data = bData; // all the components are set == default except for K
      
      // Terms for turbulent intensity
      const CFuint iK = getModel()->getFirstScalarVar(0);
      data[iK]= currState[4];
      data[iK+1]= currState[5];
    }
  }
  
  if(nbEqSS == 3){
    if (iVar < 4) {  // u + du // v + dv // T + dT // p + dp
      computePhysicalData(currState, data);
      const CFuint iK = getModel()->getFirstScalarVar(0);
      data[iK] = bData[iK];
      data[iK+1] = bData[iK+1];
    }
    else { // k + dk  ||  omega + dOmega
      if (iVar == 4) { // k + dk
	data = bData; // all the components are set == default except for K

	// Terms for turbulent intensity
	const CFuint iK = getModel()->getFirstScalarVar(0);
	data[iK]= currState[4];
      }
      
      if (iVar == 5) { // omega + domega
	data = bData; // all the components are set == default except for Omega
	
	// Terms for turbulent intensity
	const CFuint iK = getModel()->getFirstScalarVar(0);
	data[iK+1]= currState[5];
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////

    } // namespace GammaAlpha

  } // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
