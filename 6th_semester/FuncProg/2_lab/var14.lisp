(defun square(x)
  (* x x)
  )

(defun rec-square(x)
  (if (= (length x) 0)
      nil
      (append (list (square (first x))) (rec-square (rest x)))
      )
  )

(defun map-square(x)
  (map 'list #'square x)
  )