//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Grids.hpp>
#include "perfgrap.h"
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *AlphaParameterEdit;
	TEdit *BetaParameterEdit;
	TEdit *HParameterEdit;
	TButton *CalculateButton;
	TLabel *HParameterLabel;
	TLabel *BetaParameterLabel;
	TLabel *AlphaParameterLabel;
	TLabel *OutputResultLabel;
	TImage *FunctionSImage;
	TImage *FunctionYImage;
	TLabel *NParameterLabel;
	TEdit *NParameterEdit;
	TStringGrid *FunctionOutputGrid;
	TRadioGroup *CalculateRadioGroup;
	void __fastcall CalculateButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
