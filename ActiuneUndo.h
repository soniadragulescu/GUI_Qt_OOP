#pragma once
#include "RepoFile.h"
#include "Produs.h"
#include <assert.h>


class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	RepoFile& r;
	Produs produsAdaugat;
public:
	UndoAdauga(RepoFile& r, const Produs& p) :
		r{ r },
		produsAdaugat{ p }{};
	void doUndo() override {
		this->r.remove(this->produsAdaugat);
	}
};

class UndoSterge : public ActiuneUndo {
private:
	RepoFile& r;
	Produs produsSters;
public:
	UndoSterge(RepoFile& r, const Produs& p) :
		r{ r },
		produsSters{ p }{};
	void doUndo() override {
		this->r.store(produsSters);
	}
};

class UndoModifica : public ActiuneUndo {
private:
	RepoFile& r;
	Produs vechi, nou;
public:
	UndoModifica(RepoFile& r, const Produs& vechi, const Produs& nou) :
		r{ r },
		vechi{ vechi },
		nou{ nou }{};
	void doUndo()override {
		this->r.update(nou, vechi);
	}
};
