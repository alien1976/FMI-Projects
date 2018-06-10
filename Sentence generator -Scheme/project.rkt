;;Калоян Гешев фн:45221
;;Проект - генератор на изречения 

(define (readPort p) ;; чете от файл с порт р (добавя думите в списък)
  (define x (read p))
  (if (eof-object? x)
       (begin (close-input-port p) `())
       (cons x (readPort p))))

(define (writePort p string) ;; пише във файл с порт р
  (display string)
  (write string p)
  (newline p)
  (newline p)
  (close-output-port p))

(define (readFile file);;отвяря порт p за четене с име на файла file
  (define p (open-input-file file))
  (readPort p))

(define filelist (cdr (readFile "dictionary1.txt")));;cdr тъй като ми прави проблем с български думи ми дослагва един ред отгоре

(define getword car) ;; взима изписването на думата
(define getrole cadr) ;; взима ролята на думата О,П,С,Д (определение, подлог,сказуемо,допълнение)
(define getfamily caddr) ;; взима рода на думата мж - мъжки род, ж - женски род, ср - среден род,
;; ед - единствено число,мн-множествено число (за сказуемите или мн. за подлозите и определенията)

;;изваждаме всички подлози, определения, сказуеми и допълнения в отделни списъци
(define podlozi (filter (lambda(x)(equal? (getrole x) "П")) filelist))
(define opredeleniq (filter (lambda(x)(equal? (getrole x) "О")) filelist))
(define skazuemi (filter (lambda(x)(equal? (getrole x) "С")) filelist))
(define dopulneniq (filter (lambda(x)(equal? (getrole x) "Д")) filelist))

(define (getverb family) ;; взимаме сказуемо family - ед. или мн. число
  (if (equal? family "мн")
    (let ((newlist (filter (lambda(x)(equal? (getfamily x) family)) skazuemi)))
      (list-ref newlist (random (length newlist))))
    (let ((newlist (filter (lambda(x)(not (equal? (getfamily x) "мн"))) skazuemi)))
      (list-ref newlist (random (length newlist))))))

(define (getadj podlog) ;; взимаме определение
  (let ((newlist (filter (lambda(x)(equal? (getfamily x) (getfamily podlog))) opredeleniq)))
                  (list-ref newlist (random (length newlist)))))

(define (getRandomSentence) ;; генериира просто изречение
  (define p (open-output-file "sentences.txt" `text `append))
  (let* ((podlog (list-ref podlozi (random (length podlozi))))
         (opredelenie (getadj podlog))
         (skazuemo (getverb (getfamily podlog)))
         (dopulnenie (list-ref dopulneniq (random (length dopulneniq))))
         (result (string-append (getword opredelenie) " " (getword podlog) " " (getword skazuemo) " " (getword dopulnenie))))
    (writePort p result)))

(define (getpodlog2 podlog1) ;; взимаме 2-ри подлог различен от първия
  (define podlog2 (list-ref podlozi (random (length podlozi))))
  (if (equal? podlog2 podlog1)
      (getpodlog2 podlog1)
      podlog2))

(define (getRandomComplexSentence) ;; генерира сложно изречение
  (define p (open-output-file "sentences.txt" `text `append))
  (let* ((podlog1 (list-ref podlozi (random (length podlozi))))
        (opredelenie1 (getadj podlog1))
        (podlog2 (getpodlog2 podlog1))
        (opredelenie2 (getadj podlog2))
        (skazuemo (getverb "мн"))
        (dopulnenie (list-ref dopulneniq (random (length dopulneniq))))
        (result (string-append (getword opredelenie1) " " (getword podlog1) " и " (getword opredelenie2) " "
                       (getword podlog2) " " (getword skazuemo) " " (getword dopulnenie))))
     (writePort p result)))
