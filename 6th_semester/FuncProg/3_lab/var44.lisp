(defun matrix-t1-t2 (n)
  (if (>= n 1)
      (let ((arr (make-array (list n n) :initial-element 1)) (len (- n 1)) (counter 1) (i 0) (j 0) (state 'right))
        (progn
          (loop while (/= counter (* n n))
                do ( case state

                     ('right
                      (progn
                        (setf (aref arr i j) counter)
                        (incf j)
                        (incf counter)
                        (setf (aref arr i j) counter)
                        (if (/= i len) (setf state 'down-diag) (setf state 'up-diag))
                        )
                      )

                     ('down-diag
                      (progn
                        (loop while (and (> j 0) (/= i len))
                              do( progn
                                  (incf i)
                                  (decf j)
                                  (incf counter)
                                  (setf (aref arr i j) counter)
                                  )
                              )
                        (if (/= i len) (setf state 'down) (setf state 'right))
                        )
                      )

                     ('down
                      (progn
                        (setf (aref arr i j) counter)
                        (incf i)
                        (incf counter)
                        (setf (aref arr i j) counter)
                        (if (/= j len) (setf state 'up-diag) (setf state 'down-diag))
                        )
                      )

                     ('up-diag
                      (progn
                        (loop while (and (> i 0) (/= j len))
                              do( progn
                                  (decf i)
                                  (incf j)
                                  (incf counter)
                                  (setf (aref arr i j) counter)
                                  )
                              )
                        (if (/= j len) (setf state 'right) (setf state 'down))
                        )
                      )
                     )
                )
          arr
          )
        )
      (progn (format t "please enter correct length~%") nil)
      )
  )

