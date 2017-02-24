Every function, class, or any other code should get through here before being merged into master branch. These attributes has to be provided:
 
 - Specification
 - Code review (should include a link to a review)
 
 and those three has to be green:
 - Conformance
 - Tests
 - Documentation
 
 <h2>Template:</h2>
 
  - <h4>Specification: </h4>
  
  - <h4>Code Review: </h4>
 
  - <h4>Conformance: </h4>
  
  - <h4>Tests: </h4>
   
  - <h4>Documentation: </h4>
 
##sliding_window

 - <h4>Conformance: <font color=green>maximum</font> </h4>
 
   Code now has very clear semantics which enable very powerful and clear combinations.
 
 - <h4> Tests: <font color="green">good</font>, but could be better</h4>
 
   There is a test or two, but all of them are premade and non randomized, so the code might be silently hiding bugds inside.
 
 - <h4> Documentation: <font color="green">good</font></h4>
 
   Documentation provides solid start for users.
 
 ##transform_iterator (ex preprocessing_iterator)
 
 - <h4>Specification:</h4>
 
    >Given `Functor functor` that conforms `Callable`, `Iterator iterator` that conforms `OutputIterator` create a new iterator that instead of assigning `value_type`s directly, apply `functor` first and pass the result into underlying iterator.
    
 - <h4>Code review:</h4>
 
   [Preprocessing iterator](http://codereview.stackexchange.com/questions/155866/preprocessing-iterator) (first iteration).
 
 - <h4>Conformance: <font color=green>maximum</font> </h4>
  
   After going through code review, easy of use increased and in general semantics got much clearer.
  
   Bugfix: post increment was pre incrementing. Fixed. Added full support for Iterator and OutputIterator concept.
   
   Bugfix: `transformer<>()` was incorrectly deducing types which lead to storing functor as reference. Now the transformoer will strip off references and constness.
  
  - <h4> Tests: <font color=red>very poor tests</font></h4>
  
  There is a test or two, but all of them are premade and non randomized, so the code might be silently hiding bugs inside.
  
  - <h4> Documentation: <font color=green>good</font></h4>
  
    Documentation covers most of the relevant parts of the code and explains how to use it.
    
##average

   - <h4>Specification: </h4>
   
   >Given `InputIterator first, last` (which are `InputIterator`s), optionally `T initvalue = {}`,
   compute the average of the elements denoted by iterator range `[first, last)`, starting the sum from
   `initvalue`. Does not warn if integer division or similar happens.
   
   - <h4>Code Review: too small for review</h4>
  
   - <h4>Conformance: <font color="green">full</font></h4>
   
   - <h4>Tests: <font color="green">good</font>, but could be better</h4>
    
   - <h4>Documentation: <font color="green">good</font></h4>
  
##Future plans

Document everything in this project, write tests and make all of them pass. Nuke doxygen.