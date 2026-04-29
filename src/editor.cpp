#include "editor.h"
#include "processor.h"

IrLoaderGEditor::IrLoaderGEditor(IrLoaderGProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
  loadButton.setButtonText("Load IR");
  loadButton.onClick = [this] { loadButtonClicked(); };
  addAndMakeVisible(loadButton);

  setSize(400, 300);
}

IrLoaderGEditor::~IrLoaderGEditor() {}

void IrLoaderGEditor::paint(juce::Graphics &g) {
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void IrLoaderGEditor::resized() {
  loadButton.setBounds(getLocalBounds().withSizeKeepingCentre(100, 40));
}

void IrLoaderGEditor::loadButtonClicked() {
  fileChooser = std::make_unique<juce::FileChooser>(
      "Select Impulse Response",
      juce::File::getSpecialLocation(juce::File::userHomeDirectory), "*.wav");

  auto folderChooserFlags = juce::FileBrowserComponent::openMode |
                            juce::FileBrowserComponent::canSelectFiles;

  fileChooser->launchAsync(folderChooserFlags,
                           [this](const juce::FileChooser &chooser) {
                             auto file = chooser.getResult();
                             if (file.existsAsFile()) {
                               audioProcessor.loadImpulseResponse(file);
                             }
                           });
}
