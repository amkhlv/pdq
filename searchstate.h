#ifndef SEARCHSTATE_H
#define SEARCHSTATE_H

#include <QString>

class SearchState
{
public:
    SearchState();
    bool searching;
    QString searchTerm;
    bool isOnReverse;
    bool justReversed;
    qint16 searchResultsShown;
    qint16 searchStartPage;
};

#endif // SEARCHSTATE_H
