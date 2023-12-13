#pragma once
#include "BinaryTree.h"
#include "Option.h"
#include <math.h>

class CRRPricer {
private:
#pragma region attributes
	int _depth;
	double _assetPrice;
	double _up;
	double _down;
	double _interest_rate;
	Option* _option;
	BinaryTree<double> _tree;
	BinaryTree<bool> _exercise;
	void computeTree();
#pragma endregion

public:
	CRRPricer(Option *option, int depth, double assetPrice, double up, double down, double riskFreeRate) :
		_option{option}, _depth{ depth }, _assetPrice{ assetPrice }, _up{ up }, _down{ down }, _interest_rate{ riskFreeRate } {
		//Checking for abitrage
		std::cout << depth<<" " << _down << " " << _interest_rate << " " << _up << std::endl;

		if (!(_down < _interest_rate && _interest_rate < _up)) {
			std::cerr<< "The model doesn't verify D < R < U." << _down << _interest_rate << _up << std::endl;
		}

		 _tree.setDepth(depth);

		 //Checking if it is an AsianOption
		 if (_option->isAsianOption()) {
			 throw std::runtime_error("Asian options are not supported by CRRPricer.");
		 }
		 if (_option->isAmericanOption()) {
			 _exercise.setDepth(depth);
		 }
	}

	CRRPricer(Option* option, int depth, double assetPrice, double r, double volatility)
	{
		_up = exp(volatility * sqrt(option->getExpiry() / depth)) - 1.0;
		_down = exp(-volatility * sqrt(option->getExpiry() / depth)) - 1.0;
		_interest_rate = exp(r * option->getExpiry() / depth) - 1.0;
		_assetPrice = assetPrice;
		_option = option;
		_depth = depth;

		std::cout << depth << " " << _down << " " << _interest_rate << " " << _up << std::endl;

		if (!(_down < _interest_rate && _interest_rate < _up)) {
			std::cerr << "The model doesn't verify D < R < U." << _down << _interest_rate << _up << std::endl;
		}

		_tree.setDepth(depth);

		//Checking if it is an AsianOption
		if (_option->isAsianOption()) {
			throw std::runtime_error("Asian options are not supported by CRRPricer.");
		}
		if (_option->isAmericanOption()) {
			_exercise.setDepth(depth);
		}
	}

	
	void compute();
	double get(int n, int i) const { return _tree.getNode(n, i); }
	bool getExercise(int n, int i) const { return _exercise.getNode(n, i); }
	double operator()(bool closedForm = false) ;
	double riskNeutralProbability();
};




