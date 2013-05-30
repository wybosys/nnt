;; for file.
(prefer-coding-system 'utf-8)
(setq coding-system-for-read 'utf-8)
(setq coding-system-for-write 'utf-8)

;; for cedet and ecb or other.
(setq stack-trace-on-error t)

;; package manager.
(setq package-archives '(("gnu" . "http://elpa.gnu.org/packages/")
                         ("marmalade" . "http://marmalade-repo.org/packages/")
                         ("melpa" . "http://melpa.milkbox.net/packages/")
                         ("tromey" . "http://tromey.com/elpa/")
                         ))

(when (not (file-accessible-directory-p "~/.emacs.d/lisps"))
  (make-directory "~/.emacs.d/lisps"))
(add-to-list 'load-path "~/.emacs.d/lisps/")
(add-to-list 'load-path "~/.emacs.d/auto-install/")

;; package manager.
(defun elpa-require (module &optional package)
  (if (require module nil 'noerror) nil
    (require 'package)
    (unless package-archive-contents
      (package-refresh-contents))
    (if (eq package nil)
        (package-install module)
      (package-install package))
    (message "module installed")
    (require module)
    )
  )

;; may case os-x crash. 
;(defun ai-require-file (module file)
;  (if (require module nil 'noerror) nil
;    (elpa-require 'auto-install)    
;    (auto-install-from-emacswiki file)
;    (require module)
;    )
;  )

(defun ai-require-url (module url)
  (if (require module nil 'noerror) nil
    (elpa-require 'auto-install)
    (setq auto-install-use-wget nil)
    (setq auto-install-save-confirm nil)
    (auto-install-from-url url)
    )
  (require module nil 'noerror)
  )

;; guide setting.
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(blink-cursor-mode nil)
 '(column-number-mode t)
 '(ecb-layout-window-sizes nil)
 '(ecb-options-version "2.40")
 '(global-auto-revert-mode t)
 '(global-hl-line-mode 1)
 '(global-linum-mode 1)
 '(global-tool-bar-mode nil)
 '(indent-tabs-mode nil)
 '(inhibit-startup-screen t)
 '(initial-scratch-message "")
 '(linum-format "%-5d")
 '(scroll-bar-mode (quote right))
 '(show-paren-mode t)
 '(tab-width 4))

;; in-gui or not-gui.
(defun my-maximum ()
  (interactive)
  (cond ((eq window-system 'x)
         (x-send-client-message nil 0 nil "_NET_WM_STATE" 32 '(2 "_NET_WM_STATE_MAXIMIZED_HORZ" 0))
         (x-send-client-message nil 0 nil "_NET_WM_STATE" 32 '(2 "_NET_WM_STATE_MAXIMIZED_VERT" 0))
         (sit-for 0.1)
         )
        ((eq window-system 'w32)
         (w32-send-sys-command #xf030)
         )
        ((eq window-system 'ns)
         )
      )
  )

(defun my-gui ()
  (custom-set-faces
   '(default ((t (:inherit nil :stipple nil :background "white" :foreground "black" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 98 :width normal :foundry "outline"))))
   '(linum ((t (:inherit (shadow default) :background "gray96"))))
   ) 
  ;; hl-line.
  (set-face-background 'hl-line "gray96")
  ;; other
  ;(add-hook 'window-setup-hook 'my-maximum)
  (my-maximum)
  )

(defun my-cli ()
  (custom-set-faces
   '(default ((t (:inherit nil :stipple nil :background "color-231" :foreground "black" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 98 :width normal :foundry "outline"))))
   '(linum ((t (:inherit (shadow default) :background "color-255"))))
   )
  ;; hl-line.
  (set-face-background 'hl-line "color-255")
  )

(if (not window-system)
    (my-cli)
  (my-gui)
  )

;; yes-or-no.
(defun my-mumble-or-no-p (prompt)
  "PROMPT user with a yes-or-no question, but only test for no."
  (if (string= "no"
               (downcase
                (read-from-minibuffer
                 (concat prompt "(yes[enter] or no) "))))
      nil
    t))
(defalias 'yes-or-no-p 'my-mumble-or-no-p)

;; hl-paren
(defun my-hlparen ()
  ; hl paren
  (when (ai-require-url 
	 'highlight-parentheses 
	 "http://nschum.de/src/emacs/highlight-parentheses/highlight-parentheses.el")
    (define-globalized-minor-mode global-highlight-parentheses-mode
      highlight-parentheses-mode
      (lambda ()
	(highlight-parentheses-mode t)
	))
    (global-highlight-parentheses-mode t)
    )
  ; rainbow
  (elpa-require 'rainbow-delimiters)
  (global-rainbow-delimiters-mode t)
  )
(add-hook 'prog-mode-hook 'my-hlparen)

;; yasnippet
(setq my-yas-c-comment '())
(defun my-yas ()
  (elpa-require 'yasnippet)
  (elpa-require 'yasnippet-bundle)
  )
(add-hook 'after-init-hook 'my-yas)

;; icicles.
(defun my-icicle ()
  (elpa-require 'icicles)
  (icy-mode 1)
  (add-hook 'icicle-ido-like-mode-hook
            (lambda () (setq icicle-default-value
                             (if icicle-ido-like-mode t 'insert-end))))
  )
(add-hook 'after-init-hook 'my-icicle)

;; backups.
(setq make-backup-files nil)
(defvar backup-dir "~/.emacs.d/backups/")
(setq backup-directory-alist (list (cons "." backup-dir)))

;; ignores.
(setq my-ignores '(".DS_Store" ".git" ".svn" ".cvs" ".ede\\'" "\\`~" "\\`#" ".pyc\\'" "\\`tmp" ".o\\'" "\\`_{1}" ".ropeproject" ".scc\\'" ".out\\'" ".files\\'" ".class\\'" ".symvers\\'" ".order\\'" ".properties\\'" ".dmp\\'" ".tmp\\'" ".ncb\\'" ".suo\\'" ".usr\\'" ".user\\'" ".xcuserdatad\\'" "build" "Debug" "Release" "Debug Static" "Release Static" ".cmd\\'"))

;; ido mode for fast open.
(ido-mode 1)
(dolist (ignore my-ignores)
  (add-to-list 'ido-ignore-files ignore))

;; session.
(defun my-session ()
  (elpa-require 'session)
  (elpa-require 'desktop)
  (require 'desktop)
  (session-initialize)
)
(add-hook 'after-init-hook 'my-session)

;; uniquify buffer name
(require 'uniquify)
(setq uniquify-buffer-name-style 'reverse)

;; org-mode
(require 'org)
(add-to-list 'auto-mode-alist '("\\.org\\'" . org-mode))

;; tramp
(require 'tramp)
(setq tramp-default-method "ssh")

;; bookmark
(require 'bookmark)

;; save space.
(setq-default save-place t)
(require 'saveplace)

;; vcm.
(require 'git nil 'noerror)
(require 'vc-git)

;; python.
(defun my-py-settings ()
  (setq ropemacs-guess-project t)
  (setq ropemacs-enable-autoimport t)
  (setq ropemacs-codeassist-maxfixes 3) ;; stop parse if error N times
  (setq ropemacs-autoimport-modules '("os" "shutil" "sys" "logging"))
)
(add-hook 'python-mode-hook 'my-py-settings)

;; cmake.
(setq auto-mode-alist
      (append
       '(("CMakeLists\\.txt\\'" . cmake-mode))
       '(("\\.cmake\\'" . cmake-mode))
       auto-mode-alist))
(autoload 'cmake-mode "cmake-mode.el" t)

;; company.
(defun my-company ()
  (elpa-require 'company)
  (global-company-mode)
)
(add-hook 'after-init-hook 'my-company)

;; cedet
(defun my-cedet-setting ()
  (setq 
   semantic-c-takeover-hideif t
   semantic-symref-tool "cscope"
   )    
  )

(defun check-expansion ()
    (save-excursion
      (if (looking-at "\\_>") t
        (backward-char 1)
        (if (looking-at "\\.") t
          (backward-char 1)
          (if (looking-at "->") t nil)))))

(defun do-yas-expand ()  
  (let ((yas/fallback-behavior 'return-nil))
      (yas/expand)))

(defun tab-indent-or-complete ()
  (interactive)
  (if (minibufferp)
      (minibuffer-complete)
    (if (or (not yas/minor-mode)
            (null (do-yas-expand)))
        (if (check-expansion)
            (company-complete-common)
          (indent-for-tab-command)))))

(defun my-cedet-keymap ()
    (local-set-key (kbd "RET") 'newline-and-indent)
    (local-set-key (kbd "TAB") 'tab-indent-or-complete)
)

(defun my-cedet-setup ()
	(require 'cedet)
	(my-cedet-setting)
	(my-cedet-keymap)
)

(defun my-cedet-launch ()
  (semantic-mode)
)

;; ecb
(defun my-ecb-layouts ()
	(setq ecb-windows-width 30)
	(ecb-layout-define "my-layout" left nil
	  (ecb-split-ver 0.4 t)
	  (if (fboundp (quote ecb-set-directories-buffer)) (ecb-set-directories-buffer) (ecb-set-default-ecb-buffer))
	  (dotimes (i 1) (other-window 1) (if (equal (selected-window) ecb-compile-window) (other-window 1)))
	  (ecb-split-ver 0.5 t)
	  (if (fboundp (quote ecb-set-sources-buffer)) (ecb-set-sources-buffer) (ecb-set-default-ecb-buffer))
	  (dotimes (i 1) (other-window 1) (if (equal (selected-window) ecb-compile-window) (other-window 1)))
	  (if (fboundp (quote ecb-set-methods-buffer)) (ecb-set-methods-buffer) (ecb-set-default-ecb-buffer))
	  (dotimes (i 2) (other-window 1) (if (equal (selected-window) ecb-compile-window) (other-window 1)))
	  (dotimes (i 3) (other-window 1) (if (equal (selected-window) ecb-compile-window) (other-window 1)))
	  )
	(ecb-layout-switch "my-layout")
)

(unless (boundp 'x-max-tooltip-size)
  	(setq x-max-tooltip-size '(80 . 40)))

(defun my-ecb-setting () 
	(setq 
		global-ede-mode t
		ecb-auto-activate t
		ecb-tip-of-the-day nil
		inhibit-startup-message t
		ecb-auto-compatibility-check nil
		ecb-version-check nil        
		)
)

(defun my-ecb-keys ()
    ;(local-set-key "." 'semantic-complete-self-insert)
    ;(local-set-key ">" 'semantic-complete-self-insert)
)

(defun my-ecb-setup ()
  (my-cedet-setup)
  (elpa-require 'ecb-autoloads 'ecb)
  (my-ecb-setting)
  (my-ecb-keys)
  (ecb-activate)
  (my-ecb-layouts)
  (my-cedet-launch)
)

;; mydev
(defun mydev ()
	(interactive)
	(my-ecb-setup)
	)
		
;; assist
(defun my-assist ()
  (elpa-require 'cl-lib)
  (ai-require-url 'eassist "http://www.emacswiki.org/emacs/download/eassist.el")
  (setq eassist-header-switches
	'(("h" . ("cpp" "cxx" "c++" "CC" "cc" "C" "c" "mm" "m"))
	  ("hh" . ("cc" "CC" "cpp" "cxx" "c++" "C"))
	  ("hpp" . ("cpp" "cxx" "c++" "cc" "CC" "C"))
	  ("hxx" . ("cxx" "cpp" "c++" "cc" "CC" "C"))
	  ("h++" . ("c++" "cpp" "cxx" "cc" "CC" "C"))
	  ("H" . ("C" "CC" "cc" "cpp" "cxx" "c++" "mm" "m"))
	  ("HH" . ("CC" "cc" "C" "cpp" "cxx" "c++"))
	  ("cpp" . ("hpp" "hxx" "h++" "HH" "hh" "H" "h"))
	  ("cxx" . ("hxx" "hpp" "h++" "HH" "hh" "H" "h"))
	  ("c++" . ("h++" "hpp" "hxx" "HH" "hh" "H" "h"))
	  ("CC" . ("HH" "hh" "hpp" "hxx" "h++" "H" "h"))
	  ("cc" . ("hh" "HH" "hpp" "hxx" "h++" "H" "h"))
	  ("C" . ("hpp" "hxx" "h++" "HH" "hh" "H" "h"))
	  ("c" . ("h"))
	  ("m" . ("h"))
	  ("mm" . ("h"))))
  (local-set-key "\M-o" 'eassist-switch-h-cpp)
  )

;; cscope
(defun my-cscope ()
  (elpa-require 'ascope)
)
	
;; c mode.
(add-to-list 'auto-mode-alist '("\\.h\\'" . c++-mode))
(defun my-c-mode ()
  (interactive)
  (setq c-basic-offset 4)
  (my-assist)	
  (my-cscope)
  ;; add yas template.
  (yas/define-snippets 'c-mode my-yas-c-comment 'cc-mode)
  )

(add-hook 'c-mode-common-hook 
          '(lambda ()
             (my-c-mode)
             (run-with-idle-timer 0.01 nil 
                                  (lambda() 
                                    (mydev))
                                  ))
)

;; verilog
(autoload 'verilog-mode "verilog-mode" "Verilog mode" t )
(add-to-list 'auto-mode-alist '("\\.[ds]?vh?\\'" . verilog-mode))
(setq verilog-indent-level             3
      verilog-indent-level-module      3
      verilog-indent-level-declaration 3
      verilog-indent-level-behavioral  3
      verilog-indent-level-directive   1
      verilog-case-indent              2
      verilog-auto-newline             t
      verilog-auto-indent-on-newline   t
      verilog-tab-always-indent        t
      verilog-auto-endcomments         t
      verilog-minimum-comment-distance 40
      verilog-indent-begin-after-if    t
      verilog-auto-lineup              'declarations
      verilog-highlight-p1800-keywords nil
      verilog-linter             "my_lint_shell_command"
      )

;; php
(autoload 'php-mode "php-mode" "PHP mode" t)
(add-to-list 'auto-mode-alist '("\\.php\\'" . php-mode))

;; script style.
(defconst my-c-style
  '(
    (c-tab-always-indent . t)
    (c-comment-only-line-offset . 4)
    (c-hanging-braces-alist     . ((substatement-open before)
                                   (brace-list-open)
                                   ))
    (c-hanging-colons-alist     . ((member-init-intro before)
                                   (inher-intro)
                                   (case-label after)
                                   (label after)
                                   (access-label after)
                                   ))
    (c-cleanup-list             . (scope-operator
                                   empty-defun-braces
                                   defun-close-semi))
    (c-offsets-alist            . ((arglist-close . c-lineup-arglist)
                                   (substatement-open . 0)
                                   (access-label      . -)
                                   (case-label        . +)
                                   (inline-open       . 0)
                                   (block-open        . 0)
                                   (knr-argdecl-intro . -)
                                   (innamespace . 0)
                                   ))
    ;(c-echo-syntactic-information-p . t) // verbose while indent.
    ) 
  "My C script style."
  )
(c-add-style "my-cstyle" my-c-style)

(setq c-default-style 
      '((c-mode . "my-cstyle") ;; stroustrup
        (c++-mode . "my-cstyle") 
        (java-mode . "java") 
        (awk-mode . "awk") 
        (other . "gnu")
        ))

;; undo mode.
(defun my-undo ()
  (elpa-require 'undo-tree)
  (undo-tree-mode)
)

(add-hook 'after-init-hook 'my-undo)

;; auto compelete.
;(require 'auto-complete)
;(global-auto-complete-mode t)

;; buffer
(defun my-switch-to-lastbuffer ()
	(interactive)
	(switch-to-buffer nil)
)

;; global bind keys.
(global-set-key (kbd "C-x <left>") 'my-switch-to-lastbuffer)
(global-set-key (kbd "C-x <right>") 'other-window)
(global-set-key (kbd "C-x C-<up>") 'scroll-other-window-down)
(global-set-key (kbd "C-x C-<down>") 'scroll-other-window)
(global-set-key (kbd "C-<tab>") 'my-switch-to-lastbuffer)
(global-set-key (kbd "<mouse-1>") 'mouse-set-point)
(global-set-key (kbd "<down-mouse-1>") 'mouse-drag-region)
(global-set-key (kbd "C-<down>") 'forward-paragraph)
(global-set-key (kbd "C-<up>") 'backward-paragraph)
(global-set-key (kbd "<end>") 'bookmark-set)
(global-set-key (kbd "<home>") 'bookmark-jump)
(global-set-key (kbd "C-x C-f") 'ido-find-file)
