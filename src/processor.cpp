#include "processor.h"
#include "editor.h"

IrLoaderGProcessor::IrLoaderGProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(
          BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
      )
#endif
{
}

IrLoaderGProcessor::~IrLoaderGProcessor() {}

const juce::String IrLoaderGProcessor::getName() const {
  return JucePlugin_Name;
}

bool IrLoaderGProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool IrLoaderGProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool IrLoaderGProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double IrLoaderGProcessor::getTailLengthSeconds() const { return 0.0; }

int IrLoaderGProcessor::getNumPrograms() { return 1; }

int IrLoaderGProcessor::getCurrentProgram() { return 0; }

void IrLoaderGProcessor::setCurrentProgram(int index) {
  juce::ignoreUnused(index);
}

const juce::String IrLoaderGProcessor::getProgramName(int index) {
  juce::ignoreUnused(index);
  return {};
}

void IrLoaderGProcessor::changeProgramName(int index,
                                                const juce::String &newName) {
  juce::ignoreUnused(index, newName);
}

void IrLoaderGProcessor::prepareToPlay(double sampleRate,
                                            int samplesPerBlock) {
  juce::dsp::ProcessSpec spec;
  spec.sampleRate = sampleRate;
  spec.maximumBlockSize = samplesPerBlock;
  spec.numChannels = getTotalNumOutputChannels();

  convolution.prepare(spec);
}

void IrLoaderGProcessor::releaseResources() {}

bool IrLoaderGProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
  juce::ignoreUnused(layouts);
  return true;
#else
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    return false;

#if !JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}

void IrLoaderGProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                           juce::MidiBuffer &midiMessages) {
  juce::ignoreUnused(midiMessages);
  juce::ScopedNoDenormals noDenormals;

  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  juce::dsp::AudioBlock<float> block(buffer);
  juce::dsp::ProcessContextReplacing<float> context(block);

  convolution.process(context);
}

bool IrLoaderGProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor *IrLoaderGProcessor::createEditor() {
  return new IrLoaderGEditor(*this);
}

void IrLoaderGProcessor::getStateInformation(juce::MemoryBlock &destData) {
  juce::ignoreUnused(destData);
}

void IrLoaderGProcessor::setStateInformation(const void *data,
                                                  int sizeInBytes) {
  juce::ignoreUnused(data, sizeInBytes);
}

void IrLoaderGProcessor::loadImpulseResponse(const juce::File &file) {
  convolution.loadImpulseResponse(file, juce::dsp::Convolution::Stereo::yes,
                                  juce::dsp::Convolution::Trim::no, 0);
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new IrLoaderGProcessor();
}
