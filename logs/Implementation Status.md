Every function, class, or any other code should get through here before being merging into master branch. These attributes has to be provided:
 
 - Specification
 - Code review (should include a link to a review)
 
 and those three has to be green:
 - Conformance
 - Tests
 - Documentation
 
##sliding_window

 - <h4>Conformance: <font color=green>possible full</font> </h4>
 
   Conformance is slightly severed here, because templates created some restrictions.
 
 - <h4> Tests: <font color=red>very poor tests</font></h4>
 
   There is a test or two, but all of them are premade and non randomized, so the code might be silently hiding bugds inside.
 
 - <h4> Documentation: <font color=yellow>average</font></h4>
 
   Documentation is present and covers the main parts of the code. It could use an example or two.
 
 ##transform_iterator (ex preprocessing_iterator)
 
 - <h4>Specification:</h4>
 
    >Given `Functor functor` that conforms `Callable`, `Iterator iterator` that conforms `OutputIterator` create a new iterator that instead of assigning `value_type`s directly, apply `functor` first and pass the result into underlying iterator.
    
 - <h4>Code review:</h4>
 
   [Preprocessing iterator](http://codereview.stackexchange.com/questions/155866/preprocessing-iterator) (first iteration).
 
 - <h4>Conformance: <font color=green>maximum</font> </h4>
  
   After going through code review, easy of use increased and in general semantics got much clearer.
  
   Bugfix: post increment was pre incrementing. Fixed. Added full support for Iterator and OutputIterator concept.
  
  - <h4> Tests: <font color=red>very poor tests</font></h4>
  
  There is a test or two, but all of them are premade and non randomized, so the code might be silently hiding bugds inside.
  
  - <h4> Documentation: <font color=green>good</font></h4>
  
    Documentation covers most of the relevant parts of the code and explains how to use it.
  
##Future plans

Document everything in this project, write tests and make all of them pass. Nuke doxygen.