#include "searchstate.h"
#include <QString>

bool searching;
QString searchTerm;
bool isOnReverse;
bool justReversed;
qint16 searchResultsShown;

SearchState::SearchState() :
    searching(false),
    searchTerm(QString("")),
    isOnReverse(false),
    justReversed(false),
    searchResultsShown(0),
    searchStartPage(0)
{

}
