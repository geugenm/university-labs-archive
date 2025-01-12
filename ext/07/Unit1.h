//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TLab7 : public TForm
{
__published:	// IDE-managed Components
	TLabel *InititalsInputLabel;
	TEdit *InitialsInputEdit;
	TEdit *InputRatingMathEdit;
	TButton *AddNewUserButton;
	TButton *OpenUserFileButton;
	TButton *CreateUserFileButton;
	TButton *SaveUserFileButton;
	TOpenDialog *OpenUserFileDialog;
	TButton *EditUserButton;
	TButton *DeleteUserButton;
	TStringGrid *OutputGrid;
	TEdit *InputRatingPhysEdit;
	TEdit *InputRatingITEdit;
	TLabel *InputMathRatingLabel;
	TLabel *InputPhysRatingLabel;
	TLabel *InputITRatingLabel;
	TSaveDialog *SaveUserFileDialog;
	TEdit *UserGroupInputEdit;
	TLabel *UserGroupInputLabel;
	TButton *FindSpecialUsers;
	TButton *UserSortAlphButton;
	TButton *UserSortGrpButton;
	TButton *UserSortPhysButton;
	TButton *UserSortMathButton;
	TButton *UserSortITButton;
	TButton *UserSortAvrgButton;
	void __fastcall SaveUserFileButtonClick(TObject *Sender);
	void __fastcall AddNewUserButtonClick(TObject *Sender);
	void __fastcall OpenUserFileButtonClick(TObject *Sender);
	void __fastcall CreateUserFileButtonClick(TObject *Sender);
	void __fastcall UserSortAlphButtonClick(TObject *Sender);
	void __fastcall DeleteUserButtonClick(TObject *Sender);
	void __fastcall EditUserButtonClick(TObject *Sender);
	void __fastcall FindSpecialUsersClick(TObject *Sender);
	void __fastcall UserSortGrpButtonClick(TObject *Sender);
	void __fastcall UserSortPhysButtonClick(TObject *Sender);
	void __fastcall UserSortMathButtonClick(TObject *Sender);
	void __fastcall UserSortITButtonClick(TObject *Sender);
	void __fastcall UserSortAvrgButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TLab7(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLab7 *Lab7;
//---------------------------------------------------------------------------
#endif
