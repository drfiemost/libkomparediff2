/**************************************************************************
**                             parserbase.h
**                              -------------------
**      begin                   : Tue Jul 30 23:53:52 2002
**      copyright               : (C) 2002-2003 by Otto Bruggeman
**      email                   : otto.bruggeman@home.nl
**
***************************************************************************/
/***************************************************************************
**
**   This program is free software; you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation; either version 2 of the License, or
**   ( at your option ) any later version.
**
***************************************************************************/

#ifndef _DIFF2_PARSERBASE_H
#define _DIFF2_PARSERBASE_H

#include <qregexp.h>

#include "kompare.h"
#include "difference.h"
#include "diffmodel.h"

class QStringList;
class QString;

namespace Diff2
{

class ParserBase
{
public:
	ParserBase( const QStringList& diff );
	virtual ~ParserBase();

public:
	enum Kompare::Format format() { return determineFormat(); };
	QPtrList<DiffModel>* parse();

protected:
	virtual bool parseContextDiffHeader();
	virtual bool parseEdDiffHeader();
	virtual bool parseNormalDiffHeader();
	virtual bool parseRCSDiffHeader();
	virtual bool parseUnifiedDiffHeader();

	virtual bool parseContextHunkHeader();
	virtual bool parseEdHunkHeader();
	virtual bool parseNormalHunkHeader();
	virtual bool parseRCSHunkHeader();
	virtual bool parseUnifiedHunkHeader();

	virtual bool parseContextHunkBody();
	virtual bool parseEdHunkBody();
	virtual bool parseNormalHunkBody();
	virtual bool parseRCSHunkBody();
	virtual bool parseUnifiedHunkBody();

	virtual QPtrList<DiffModel>* parseContext();
	virtual QPtrList<DiffModel>* parseEd();
	virtual QPtrList<DiffModel>* parseNormal();
	virtual QPtrList<DiffModel>* parseRCS();
	virtual QPtrList<DiffModel>* parseUnified();

protected:
	/** What is format of the diff */
	virtual enum Kompare::Format determineFormat();

protected:
	// Regexps for context parsing
	QRegExp m_contextDiffHeader1;
	QRegExp m_contextDiffHeader2;

	QRegExp m_contextHunkHeader1;
	QRegExp m_contextHunkHeader2;
	QRegExp m_contextHunkHeader3;

	QRegExp m_contextHunkBodyRemoved;
	QRegExp m_contextHunkBodyAdded;
	QRegExp m_contextHunkBodyChanged;
	QRegExp m_contextHunkBodyContext;
	QRegExp m_contextHunkBodyLine; // Added for convenience

	// Regexps for normal parsing
	QRegExp m_normalDiffHeader;

	QRegExp m_normalHunkHeaderAdded;
	QRegExp m_normalHunkHeaderRemoved;
	QRegExp m_normalHunkHeaderChanged;

	QRegExp m_normalHunkBodyRemoved;
	QRegExp m_normalHunkBodyAdded;
	QRegExp m_normalHunkBodyDivider;

	enum Difference::Type m_normalDiffType;

	// RegExps for rcs parsing
	QRegExp m_rcsDiffHeader;

	// Regexps for unified parsing
	QRegExp m_unifiedDiffHeader1;
	QRegExp m_unifiedDiffHeader2;

	QRegExp m_unifiedHunkHeader;

	QRegExp m_unifiedHunkBodyAdded;
	QRegExp m_unifiedHunkBodyRemoved;
	QRegExp m_unifiedHunkBodyContext;
	QRegExp m_unifiedHunkBodyLine; // Added for convenience

protected:
	const QStringList&         m_diffLines;
	DiffModel*                 m_currentModel;
	QPtrList<DiffModel>*       m_models;
	QStringList::ConstIterator m_diffIterator;

	bool                       m_singleFileDiff;
};

} // End of namespace Diff2

#endif
