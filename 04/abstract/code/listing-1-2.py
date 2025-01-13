def ld(A):
    """
    For a symmetric matrix A calculates the lower triangular
    matrix L and the diagonal matrix D such that
    that A = LDL^T. The elements a_{ij} are replaced
    by l_{ij} if i > j, and by d_i if i = j
    """
    n = len(A)
LD = np.array(A, float)
	for j in range(n):
		v = np.zeros(j+1)
		v[:j] = LD[j, :j]*LD[range(j), range(j)]
		v[j] = LD[j, j] - np.dot(LD[j, :j], v[:j])
		LD[j, j] = v[j]
		LD[j+1:, j] = (LD[j+1:, j] - np.dot(LD[j+1:, :j], v[:j]))/v[j]

	return LD
