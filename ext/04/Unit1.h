//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TLab4 : public TForm
{
__published:	// IDE-managed Components
	TLabel *ArraySizeLabel;
	TEdit *ArraySizeEdit;
	TButton *ApplyArraySizeButton;
	TStringGrid *InitialArrayGrid;
	TEdit *OutputResultField;
	TLabel *OutputResultLabel;
	TButton *GenerateNewArrayButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ApplyArraySizeButtonClick(TObject *Sender);
	void __fastcall GenerateNewArrayButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TLab4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLab4 *Lab4;
//---------------------------------------------------------------------------
#endif
