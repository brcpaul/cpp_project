#include "AsianCallOption.h"


/// <summary>
/// AsianCallOption function in order to calculate the payoff for an asian call option
/// </summary>
/// <returns> the payoff of the asian call option </returns>
double AsianCallOption::payoff() {
	double price_smoothed = payoffPath(asOption->getTimeSteps());
	if (price_smoothed >= _strike) {
		return price_smoothed - _strike;
	}
	else return 0.0;
}

