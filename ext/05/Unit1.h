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
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *ArraySizeLabel;
	TLabel *MatrixWidthLabel;
	TLabel *MatrixHeightLabel;
	TEdit *MatrixWidthEdit;
	TEdit *MatrixHeightEdit;
	TButton *ApplyMatrixSizeButton;
	TEdit *OutputResultField;
	TLabel *OutputResultLabel;
	TStringGrid *MatrixGrid;
	TButton *GenerateNewMatrixButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ApplyMatrixSizeButtonClick(TObject *Sender);
	void __fastcall GenerateNewMatrixButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
