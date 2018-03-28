(defun  FixedPoint (func val eps)
  (let
      (
       (curVal (funcall func val))
       )
    (if (~= curVal val eps)
        val
        (FixedPoint func curVal eps)
        )
    )
  )

(defun ~= (x y eps)
  (<= (abs (- x y)) eps)
  )

(defconstant EPSILON 0.0001)
(defconstant START_VAL 10000)
(defconstant GOLDEN_RATIO (/ (+ (sqrt 5.0) 1.0) 2.0))

(defun Task1Var40 (startingVal eps)
  (let
      (
       (fixedPoint (FixedPoint #'(lambda (x) (+ (/ 1.0 x) 1.0)) startingVal eps))
       )
    (format t "epsilon is ~A~%" eps)
    (format t "starting value is ~A~%" startingVal)
    (format t "Golden ratio is ~A~%" GOLDEN_RATIO)
    (format t "Fixed point of f(x) = 1 + 1 / x is ~A~%" fixedPoint)
    (format t "Are they close? ~A~%" (~= GOLDEN_RATIO fixedPoint eps))
    )
  )

(Task1Var40 START_VAL EPSILON)

