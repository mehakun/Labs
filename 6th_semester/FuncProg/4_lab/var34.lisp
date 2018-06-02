(defun find-word (word text)
  (if (and (not (null word)) (/= (length word) 0))
      (let
          ((word_index NIL) (sentences_amount -1) (not-null (lambda (o)(not (null o)))))
        (progn
          (loop for sentence in text
                until (funcall not-null word_index)
                do (progn
                     (incf sentences_amount)
                     (setf word_index (search word sentence))
                     )
                )
          (if (funcall not-null word_index) (list word_index sentences_amount) NIL)
          )
        )
      NIL
      )
  )