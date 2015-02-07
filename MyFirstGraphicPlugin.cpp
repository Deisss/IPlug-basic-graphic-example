#include "MyFirstGraphicPlugin.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"
#include "MyGraphicControl.h"

const int kNumPrograms = 1;

enum EParams
{
  kGain = 0,
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,

  kGainX = 100,
  kGainY = 100,
  kKnobFrames = 60
};

MyFirstGraphicPlugin::MyFirstGraphicPlugin(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mGain(1.)
{
  TRACE;

  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kGain)->InitDouble("Gain", 50., 0., 100.0, 0.01, "%");
  GetParam(kGain)->SetShape(2.);

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  //pGraphics->AttachPanelBackground(&COLOR_RED);
  pGraphics->AttachPanelBackground(&COLOR_WHITE);

  pGraphics->AttachControl(new MyGraphicControl(this, IRECT(0, 0, kWidth, kHeight)));

  /*IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);

  pGraphics->AttachControl(new IKnobMultiControl(this, kGainX, kGainY, kGain, &knob));*/

  AttachGraphics(pGraphics);

  //MakePreset("preset 1", ... );
  MakeDefaultPreset((char *) "-", kNumPrograms);
}

MyFirstGraphicPlugin::~MyFirstGraphicPlugin() {}

void MyFirstGraphicPlugin::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  // Mutex is already locked for us.

  double* in1 = inputs[0];
  double* in2 = inputs[1];
  double* out1 = outputs[0];
  double* out2 = outputs[1];

  for (int s = 0; s < nFrames; ++s, ++in1, ++in2, ++out1, ++out2)
  {
    *out1 = *in1 * mGain;
    *out2 = *in2 * mGain;
  }
}

void MyFirstGraphicPlugin::Reset()
{
  TRACE;
  IMutexLock lock(this);
}

void MyFirstGraphicPlugin::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);

  switch (paramIdx)
  {
    case kGain:
      mGain = GetParam(kGain)->Value() / 100.;
      break;

    default:
      break;
  }
}
