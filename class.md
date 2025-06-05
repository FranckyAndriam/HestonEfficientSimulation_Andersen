```mermaid
classDiagram
  %%===================  Schéma de variance (1 d)  ===================
  class Variance {
    <<abstract>>
    + step(...)
    + clone()
  }
  class QEScheme
  class TGScheme
  Variance <|-- QEScheme
  Variance <|-- TGScheme

  %%===================  Modèles stochastiques 1 d  ==================
  class Model {
    <<abstract>>
    + drift_term(...)
    + diffusion_term(...)
    + clone()
  }
  class BlackScholesModel
  class DupireLocalVolatilityModel
  Model <|-- BlackScholesModel
  Model <|-- DupireLocalVolatilityModel

  class ImpliedVolatilitySurface
  DupireLocalVolatilityModel --> ImpliedVolatilitySurface : « utilise »

  %%===================  Modèles stochastiques 2 d  ==================
  class Model2D {
    <<abstract>>
    + step(...)
    + clone()
  }
  class BroadieKayaScheme {
    - kappa, theta, epsilon, rho, r : double
    - gamma1, gamma2               : double
    - _variance_scheme             : const Variance*
  }
  Model2D <|-- BroadieKayaScheme
  BroadieKayaScheme --> Variance : « utilise »

  %%===================  Générateur aléatoire  =======================
  class StandardGaussianGenerator

  %%===================  Simulateurs de trajectoires  ================
  class PathSimulator {
    <<abstract>>
    - _time_points      : vector<double>
    - _model            : Model*
    - _initial_value    : double
    - _normal_generator : StandardGaussianGenerator
    + path() : vector<double>
  }
  class EulerPathSimulator
  PathSimulator <|-- EulerPathSimulator
  PathSimulator --> Model

  class PathSimulator2D {
    - _time_points : vector<double>
    - _model       : Model2D*
    - _S0, _V0     : double
    + path()
    + variance_path()
  }
  PathSimulator2D --> Model2D

  %%===================  Payoff & Pricing  ===========================
  class Payoff {
    <<abstract>>
    - _risk_free_rate : double
    + discounted_payoff(...)
  }
  class EuropeanOptionPayoff {
    - _strike      : double
    - _option_type : Call_Put
  }
  Payoff <|-- EuropeanOptionPayoff

  class MonteCarlo {
    - _number_simulations : size_t
    - _path_simulator     : const PathSimulator*
    - _path_simulator2d   : const PathSimulator2D*
    - _payoff             : const Payoff*
    + price() : double
  }
  MonteCarlo --> Payoff
  MonteCarlo --> PathSimulator
  MonteCarlo --> PathSimulator2D

  %%===================  Pricing semi-analytique & outils divers  ====
  class FourierPricer
  class ThomasSolver
