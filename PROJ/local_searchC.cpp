#include "local_searchC.h"

/*
    Constructor of the class.
*/
localSearch::localSearch() {

}

/*
    Implements hill climbing algorithm.
*/
State localSearch::hillClimbing(State current, int &iteration) {
    State next;
    while(true) {
        next = current.bestSuccessor();
        if(current.heuristica() <= next.heuristica()) {
            return current;
        }
        current = next;
        ++iteration;
    }
    return State();
}
