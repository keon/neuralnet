#include <iostream>
#define MAX2(a, b) (a) > (b) ? (a) : (b)

class Neuron
{
 public: // attributes
  double w_; // weight of one input
  double b_; // bias

  double input_, output_; //saved for back propagation

 public: //behaviors
  double getActivation(const double& x)
  {
    // for linear or identity activation functions
     return x;

    // for ReLu activation functions
    //return MAX2(0.0, x);
  }
  double feedForward(const double& _input)
  {
    input_ = _input;

    // output y = f(\sigma)
    // \sigma = w_ * input x + b
    // for multiple inputs,
    // \sigma = w0_ * x0_ + w1_ * x0_ ... + b

    const double sigma = w_ * input_ + b_;

    output_ = getActivation(sigma);
    return output_;
  }

  double getActivationGradient(const double& x)
  {
    // linear or identity activation function
    return 1.0;

    // ReLU if (x > 0.0) return 1.0; else 0.0
  }
  void propagateBackward(const double& target)
  {
    const double alpha = 0.1; //learning rate
    const double grad = (output_ - target) * getActivationGradient(output_);

    w_ -= alpha * grad * input_; // last input_ came from d
    b_ -= alpha * grad * 1.0; // last 1.0 came from d(wx+b)/db =1
  }

  void feedForwardAndPrint(const double& input)
  {
    std::cout << input << " -> " << feedForward(input) << std::endl;
  }
};

int main()
{
  Neuron my_neuron;
  my_neuron.w_ = 2.0;
  my_neuron.b_ = 1.0;

  for (int r=0; r < 10; r++)
  {
    std::cout << "Training " << r << std::endl;
    my_neuron.feedForwardAndPrint(1.0);
    my_neuron.propagateBackward(4.0);
    std::cout << "w = " << my_neuron.w_ << " b = " << my_neuron.b_ << std::endl;
  }
  return 0;
}
