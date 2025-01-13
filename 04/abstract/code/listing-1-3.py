def ld_solve(A, b):
	"""
	Solves the system Ax = b using LDL^T-decomposition
	"""
	LD = ld(A)
	b = np.array(b, float)
	for i in range(1, len(b)):
		b[i] = b[i] - np.dot(LD[i, :i], b[:i])
	b[:] = b[:]/LD[range(len(b)), range(len(b))]
	for i in range(len(b)-1, -1, -1):
		b[i] = (b[i] - np.dot(LD[i+1:, i], b[i+1:]))
	return b
