#pragma once

#include "processor.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class IrLoaderGEditor : public juce::AudioProcessorEditor {
public:
  IrLoaderGEditor(IrLoaderGProcessor &);
  ~IrLoaderGEditor() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  void loadButtonClicked();

  IrLoaderGProcessor &audioProcessor;

  juce::TextButton loadButton;
  std::unique_ptr<juce::FileChooser> fileChooser;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IrLoaderGEditor)
};
