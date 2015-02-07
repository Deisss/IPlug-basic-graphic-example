#ifndef __MYFIRSTGRAPHICPLUGIN__
#define __MYFIRSTGRAPHICPLUGIN__

#include "IPlug_include_in_plug_hdr.h"

class MyFirstGraphicPlugin : public IPlug
{
public:
  MyFirstGraphicPlugin(IPlugInstanceInfo instanceInfo);
  ~MyFirstGraphicPlugin();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mGain;
};

#endif
