Every function, class, or any other code should get through here before being merged into master branch. These attributes has to be provided:
 
 - Specification
 - Code review (should include a link to a review)
 
 and those three has to be green:
 - Conformance
 - Tests
 - Documentation
 
 <h2>Template:</h2>
  
  - <h4>Code Review: </h4>
 
  - <h4>Conformance: </h4>
  
  - <h4>Tests: </h4>
   
  - <h4>Documentation: </h4>
 
##sliding_window

 - <h4>Conformance: <font color=green>maximum</font> </h4>
 
   Code now has very clear semantics which enable very powerful and clear combinations.
 
 - <h4> Tests: <font color="green">good</font>, but could be better</h4>
 
 - <h4> Documentation: <font color="green">good</font></h4>
 
   Documentation provides solid start for users.
 
 ##transform_iterator
    
 - <h4>Code review:</h4>
 
   [Preprocessing iterator](http://codereview.stackexchange.com/questions/155866/preprocessing-iterator) (first iteration).
 
 - <h4>Conformance: <font color=green>maximum</font> </h4>
  
   After going through code review, easy of use increased and in general semantics got much clearer.
  
   Bugfix: post increment was pre incrementing. Fixed. Added full support for Iterator and OutputIterator concept.
   
   Bugfix: `transformer<>()` was incorrectly deducing types which lead to storing functor as reference. 
   Now the transformer will strip off references and constness.
  
  - <h4> Tests: <font color="green">good</font></h4>
  
  - <h4> Documentation: <font color=green>good</font></h4>
  
    Documentation establishes more clear wording and provides in depth understanding of the code.
    
##average
   
   - <h4>Code Review: too small for review</h4>
  
   - <h4>Conformance: <font color="green">full</font></h4>
   
   - <h4>Tests: <font color="green">good</font>, but could be better</h4>
    
   - <h4>Documentation: <font color="green">good</font></h4>
   
##scope_exit
   
   - <h4>Code Review: </h4>
   
   [scope_exit macro](http://codereview.stackexchange.com/questions/145801/scope-exit-macro)
  
   - <h4>Conformance: <font color="green">great</font></h4>
   
   The `__LINE__` macro could be replaced by `__COUNTER__`, but for some reason
   it seems like `__COUNTER__` does not expand multiple times to something different.
   
   - <h4>Tests: <font color = "green">great</font></h4>
   
   Tests are very thorough and cover every possible usage vector of `scope_exit`.
    
   - <h4>Documentation: <font color="green">good</font></h4>
   
##enable_sfinae [small]

  The code is too small to test. Documentation will be 
  merged with a general header, probably
   
##stumbled_iterator

   - <h4>Conformance: <font color="green">maximum</font></h4>
   
   - <h4>Tests: <font color = "green">great</font></h4>
   
   - <h4>Documentation: <font color = "green">good</font> </h4>
   
Candidate for removal.

##benchmark [deprecated]

  - <h4>Code Review: None yet</h4>
 
  - <h4>Conformance: maximum</h4>
  
  - <h4>Tests: yes, user controlled</h4>
   
  - <h4>Documentation: none yet</h4>  
  
##Future plans

Document everything in this project, write tests and make all of them pass. Nuke doxygen.
