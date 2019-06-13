/*
  ==============================================================================

    ParamSmooth.h
    Created: 17 May 2019 5:32:20pm
    Author:  Taylor

  ==============================================================================
*/
//This doesn't really do anything as of yet. 

#pragma once

const float dc = 1e-18;
const float PSSC = 0.0120;
class ParamSmoother
{
private:
    float steepValue;
    float integralValue;
    float srCor;
    public :
    ParamSmoother()
    {
        steepValue=integralValue=0;
        srCor=1;
    };
    float smoothStep()
    {
        integralValue = integralValue + (steepValue - integralValue) * PSSC * srCor + dc;
        return integralValue;
    }
    void setSteep(float value)
    {
        steepValue = value;
    }
    void setSampleRate(float sr)
    {
        srCor = sr / 44100;
    }
};
