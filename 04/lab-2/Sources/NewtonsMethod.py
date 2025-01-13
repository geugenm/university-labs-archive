import sympy
import colorama
import os

colorama.init()
sympy.interactive.printing.init_printing(use_unicode=True)

x1, x2, x3 = sympy.symbols('x1:4')


class NewtonsEquation:
    acceptedResultError = 1e-9;

    def __init__(self):
        self.amountOfEquations = int();
        self.InitAmountOfEquations();

        self.equationMatrix = sympy.Matrix();
        self.InitEquationMatrix();

        self.iterationMaximum = int();
        self.InitIterationMaximum();

        self.symbolsList = list();
        self.InitSymbolsList();

        self.rootApproach = sympy.Matrix();
        self.InitCurrentApproach();

        self.iterationStep = 0;
        self.delta = sympy.Matrix();

        self.ifNullCoefficient = 0.01;

    def ResetToStart(self):
        self.iterationStep = 0;
        self.delta = sympy.Matrix();
    def InitAmountOfEquations(self):
        self.amountOfEquations = int(input("Define the number of equations:"))
        if (self.amountOfEquations <= 0):
            raise ValueError("InitAmountOfEquations(): Amount of equations is less or equal zero");

    def InitIterationMaximum(self):
        self.iterationMaximum = int(input("Define iteration max step:"));
        if (self.iterationMaximum <= 0):
            raise ValueError("InitIterationMaximum(): Iteration maximum step must be bigger than zero");

    def InitCurrentApproach(self):
        if (self.amountOfEquations <= 0):
            raise ValueError("InitCurrentApproach(): Amount of equations is less or equal zero");

        self.rootApproach = sympy.Matrix();

        for i in range(0, self.amountOfEquations):
            currentApproach = float(input("Define approach for x{0}:".format(i + 1)));

            if (type(currentApproach) is not float) and (type(currentApproach) is not int):
                raise TypeError("InitCurrentApproach(): Float or int approach expected")

            self.rootApproach = self.rootApproach.row_insert(i, sympy.Matrix([currentApproach]));

        self.InitIfNullCoefficient();

    def InitEquationMatrix(self):
        if (self.amountOfEquations <= 0):
            raise ValueError("InitEquationMatrix(): Amount of equations is less or equal zero");

        self.equationMatrix = sympy.Matrix();

        for i in range(0, self.amountOfEquations):
            currentExpression = sympy.parse_expr(input("Define {0} equation:".format(i + 1)));
            self.equationMatrix = self.equationMatrix.row_insert(i, sympy.Matrix([currentExpression]));
            sympy.pprint(currentExpression);
            print('Expression № {0}/{1} parsing status: '.format(i + 1, self.amountOfEquations) + colorama.Fore.GREEN + '[OK]' + colorama.Fore.RESET)

    def InitIfNullCoefficient(self):
        for i in range(0, self.amountOfEquations):
            if (self.rootApproach[i, 0] == 0):
                self.ifNullCoefficient = float(input("Define if null approach  coefficient:"));
                if (type(self.ifNullCoefficient) is not float) and (type(self.ifNullCoefficient) is not int):
                    raise TypeError("InitIsNullCoefficient(): Float or int approach expected")
                return

    def InitSymbolsList(self):
        self.symbolsList = list(self.equationMatrix.free_symbols);

    def IterationSolve(self):
        jacobian_matrix = (self.equationMatrix.jacobian([self.symbolsList[0:]]));

        jacobian_framed = jacobian_matrix;
        function_framed = self.equationMatrix;

        for i in range(0, self.amountOfEquations):
            if (self.rootApproach[i, 0] == 0):
                jacobian_framed = jacobian_framed.subs(self.symbolsList[i], self.ifNullCoefficient);
                function_framed = function_framed.subs(self.symbolsList[i], self.ifNullCoefficient);
            else:
                jacobian_framed = jacobian_framed.subs(self.symbolsList[i], self.rootApproach[i, 0]);
                function_framed = function_framed.subs(self.symbolsList[i], self.rootApproach[i, 0]);

        function_framed = -function_framed;
        self.delta = jacobian_framed.solve(function_framed);

        self.rootApproach = self.rootApproach + self.delta;
        self.iterationStep += 1;

    def Print(self):
        print('-' * 64);
        print(colorama.Fore.LIGHTCYAN_EX + '\nCurrent iteration is {0}/{1}\n'.format(self.iterationStep, self.iterationMaximum));

        print(colorama.Fore.YELLOW + 'Current approach:');
        current_root = self.rootApproach;
        sympy.pprint(current_root.col_insert(0, sympy.Matrix([self.symbolsList[0:]]).transpose()));

        print(colorama.Fore.LIGHTBLUE_EX + '\nCurrent delta:');
        current_delta = self.delta;
        sympy.pprint(abs(current_delta.col_insert(0, sympy.Matrix([self.symbolsList[0:]]).transpose())));

        print('\n' + colorama.Fore.RESET);

    def GotAcceptedAccuracy(self):
        for i in range(0, self.amountOfEquations):
            if (abs(self.delta[i, 0]) <= abs(self.acceptedResultError)):
                return True;

        return False;

    def ApplyDialog(self):
        userChoice = str(input("Are you sure? [Y/N]"));
        if (userChoice.lower() == 'y'):
            return True;
        if (userChoice.lower() == 'n'):
            return False;
        else:
            print('ApplyDialog(): Unknown option. Type Y or N \n');
            self.ApplyDialog();

    def EditInputs(self):
        print('Choose anything to edit:\n');
        print('[1] Maximal iterations amount');
        print('[2] Initial root approach');
        print('[3] If null coefficient approach');
        print('[4] Nothing. Exit');
        userChoice = int(input(':'));
        match userChoice:
            case 1:
                if (self.ApplyDialog() == True):
                    self.ResetToStart();
                    self.InitIterationMaximum();
                    self.InitCurrentApproach();
                    self.SolveCycle();
                return;
            case 2:
                if (self.ApplyDialog() == True):
                    self.ResetToStart();
                    self.InitCurrentApproach();
                    self.SolveCycle();
                return;
            case 3:
                if (self.ApplyDialog() == True):
                    self.ResetToStart();
                    self.InitCurrentApproach();
                    self.SolveCycle();
                return;
            case 4:
                exit(0);
            case _:
                print('EditInputs(): Unknown option. Try again');
                self.EditInputs();

    def EditInputsDialog(self):
        userChoice = str(input("Do you want to edit any data? [Y/N]:"));
        if (userChoice.lower() == 'y'):
            self.EditInputs();
        elif (userChoice.lower() == 'n'):
            exit(0);
        else:
            print('EditInputsDialog(): Unknown option. Type Y or N \n');
            self.EditInputsDialog();

    def Menu(self):
        while (True):
            self.EditInputsDialog();

    def SolveCycle(self):
        for i in range(0, self.iterationMaximum):
            self.IterationSolve();
            self.Print();

            if (self.GotAcceptedAccuracy()):
                print(colorama.Fore.GREEN + 'Got accepted accuracy {0}\n'.format(self.acceptedResultError) + colorama.Fore.RESET);
                break;

        if (self.iterationStep >= self.iterationMaximum):
            print(colorama.Fore.RED + 'Proceeded to the iteration maximum {0}\n'.format(self.iterationMaximum) + colorama.Fore.RESET);

        print('Current status of the equation: ' + colorama.Fore.GREEN + '[SOLVED]' + colorama.Fore.RESET);


if __name__ == '__main__':
    alpha = NewtonsEquation();
    alpha.SolveCycle();
    alpha.Menu();
