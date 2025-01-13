namespace Gauss_Method
{
    class Maths
    {
        /// <summary>
        /// Gauss method
        /// </summary>
        /// <param name="Matrix">Initial matrix</param>
        /// <returns></returns>
        public static double[] Gauss(double[,] Matrix)
        {
            int n = Matrix.GetLength(0); // The dimensionality of the initial matrix (row)
            double[,] Matrix_Clone = new double[n, n + 1]; // Matrix Dupler
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n + 1; j++)
                    Matrix_Clone[i, j] = Matrix[i, j];

            // Straight stroke (Lower left corner jamming)
            for (int k = 0; k < n; k++) // k-line number
            {
                for (int i = 0; i < n + 1; i++) // i-number of column
                    Matrix_Clone[k, i] = Matrix_Clone[k, i] / Matrix[k, k]; // Dividing the k-string by the first term !=0 to convert it to one
                for (int i = k + 1; i < n; i++) // i-number of the next line after k
                {
                    double K = Matrix_Clone[i, k] / Matrix_Clone[k, k];
                    for (int j = 0; j < n + 1; j++) // j-number of the column of the next row after k
                        Matrix_Clone[i, j] = Matrix_Clone[i, j] - Matrix_Clone[k, j] * K; // Zoning of matrix elements below the first term converted to one
                }
                for (int i = 0; i < n; i++) // Updating, making changes to the initial matrix
                    for (int j = 0; j < n + 1; j++)
                        Matrix[i, j] = Matrix_Clone[i, j];
            }

            // Reverse stroke (Backing up the upper right corner)
            for (int k = n - 1; k > -1; k--) // k-line number
            {
                for (int i = n; i > -1; i--) // i-number of column
                    Matrix_Clone[k, i] = Matrix_Clone[k, i] / Matrix[k, k];
                for (int i = k - 1; i > -1; i--) // i-number of the next line after k
                {
                    double K = Matrix_Clone[i, k] / Matrix_Clone[k, k];
                    for (int j = n; j > -1; j--) // j-number of the column of the next row after k
                        Matrix_Clone[i, j] = Matrix_Clone[i, j] - Matrix_Clone[k, j] * K;
                }
            }

            // Separating the answers from the total matrix
            double[] Answer = new double[n];
            for (int i = 0; i < n; i++)
                Answer[i] = Matrix_Clone[i, n];

            return Answer;
        }
    }
}
