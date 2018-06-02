(defclass cart ()                ; имя класса и надклассы
  ((x :initarg :x :reader cart-x)   ; дескриптор слота x
   (y :initarg :y :reader cart-y))) ; дескриптор слота y

(defclass polar ()
  ((radius :initarg :radius :accessor radius) 	; длина >=0
   (angle  :initarg :angle  :accessor angle)))	; угол (-π;π]

(defmethod cart-x ((p polar))
  (* (radius p) (cos (angle p))))

(defmethod cart-y ((p polar))
  (* (radius p) (sin (angle p))))

(defgeneric to-cart (arg)
  (:documentation "Преобразование аргумента в декартову систему.")
  (:method ((c cart))
    c)
  (:method ((p polar))
    (make-instance 'cart
                   :x (cart-x p)
                   :y (cart-y p))) )

(defclass line ()
  ((start :initarg :start :accessor line-start)
   (end   :initarg :end   :accessor line-end)))

(defun pseudo-scalar-mul (x1 y1 x2 y2)
    (- (* x1 y2) (* y1 x2))
  )

(defun is-parallel? (line1 line2)
  (let ( (x1 (- (cart-x (line-end line1)) (cart-x (line-start line1))))
         (y1 (- (cart-y (line-end line1)) (cart-y (line-start line1))))
         (x2 (- (cart-x (line-end line2)) (cart-x (line-start line2))))
         (y2 (- (cart-y (line-end line2)) (cart-y (line-start line2))))
        )
    (= 0 (pseudo-scalar-mul x1 y1 x2 y2))
    )
  )

(defun line-parallel-p (lines)
  (if (> (length lines) 1)
      (loop for i from 1 to (- (length lines) 1)
            always (is-parallel? (nth i lines) (nth (- i 1) lines)))
      (error "length of input list must be >= 2")
      )
  )