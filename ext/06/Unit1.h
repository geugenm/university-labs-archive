// ---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

// ---------------------------------------------------------------------------
class TLab6 : public TForm {
__published: // IDE-managed Components
	TLabel *EnterStringLabel;
	TEdit *InputStringEdit;
	TLabel *AmountLabel;
	TEdit *OutputResultField;
	TButton *CloseButton;
	void __fastcall InputStringEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall CloseButtonClick(TObject *Sender);
private: // User declarations
public: // User declarations
	__fastcall TLab6(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TLab6 *Lab6;
// ---------------------------------------------------------------------------
#endif
