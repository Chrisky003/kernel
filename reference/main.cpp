void __attribute__((constructor)) func() {
	return;
}

void __attribute__((constructor)) func2() {
	return;
}

class c1 {
public:
	virtual int func() = 0;
};

class c2 : public c1 {
public:
	virtual int func() {
		return 2;
	}

	virtual int func2() {
		return 2;
	}
};

class c3 : public c2 {
public:
	virtual int func() {
		return 3;
	}

	virtual int func2() {
		return 3;
	}
};

c2 c_2;
c3 c_3;

int main() {
	int result(0);
	c1 *pc1 = &c_2;
	result = pc1->func();
	pc1 = &c_3;
	result = pc1->func();

	c2 *pc2 = &c_2;
	result = pc2->func();
	result = pc2->func2();
	pc2 = &c_3;
	result = pc2->func();
	result = pc2->func2();
	
	return 1;
}
