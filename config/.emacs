;; for file.
(prefer-coding-system 'utf-8)
(setq coding-system-for-read 'utf-8)
(setq coding-system-for-write 'utf-8)

;; for cedet and ecb or other.
(setq stack-trace-on-error t)

;; package manager.
(setq package-archives '(("gnu" . "http://elpa.gnu.org/packages/")
                         ("marmalade" . "http://marmalade-repo.org/packages/")
                         ("melpa" . "http://melpa.milkbox.net/packages/")))

(when (not (file-accessible-directory-p "~/.emacs.d/lisps"))
  (make-directory "~/.emacs.d/lisps"))
(add-to-list 'load-path "~/.emacs.d/lisps/")
(add-to-list 'load-path "~/.emacs.d/auto-install/")

(defun my-use-package (name url)
  (when (not (require name nil 'noerror))
    (setq auto-install-save-confirm nil)
    (auto-install-from-url url)
    )
  )

;; guide setting.
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(blink-cursor-mode nil)
 '(c-basic-offset 4)
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
 '(linum-format "%6d ")
 '(scroll-bar-mode (quote right))
 '(show-paren-mode t)
 '(tab-width 4)
 '(c-default-style 
   '((c-mode . "stroustrup") 
     (c++-mode . "stroustrup") 
     (java-mode . "java") 
     (awk-mode . "awk") 
     (other . "gnu")
     ))
)
 
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 ;; bk 005faf fg ffffff
 '(default ((t (:inherit nil :stipple nil :background "color-231" :foreground "black" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 98 :width normal :foundry "outline")))))

;; hl-line
(set-face-background 'hl-line "color-255")

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

;; cmake
(setq auto-mode-alist
      (append
       '(("CMakeLists\\.txt\\'" . cmake-mode))
       '(("\\.cmake\\'" . cmake-mode))
       auto-mode-alist))
(autoload 'cmake-mode "cmake-mode.el" t)

;; company.
(add-hook 'after-init-hook 'global-company-mode)

;; cedet
(defun my-cedet-setting ()
  ;; mode
  ;(semantic-load-enable-code-helpers)
  ;; global features.
  ;(global-semantic-tag-folding-mode 1)
  ;(global-semantic-idle-scheduler-mode 1) ;The idle scheduler with automatically reparse buffers in idle time.
  ;(global-semantic-idle-completions-mode 1) ;Display a tooltip with a list of possible completions near the cursor.
  ;(global-semantic-idle-summary-mode 1) ;Display a tag summary of the lexical token under the cursor.
  ;; includes.
  ;(semantic-add-system-include "/usr/src/include/")
  ;(semantic-add-system-include "/usr/src/sys/")    
  (setq 
   semantic-c-takeover-hideif t
   semantic-symref-tool "cscope"
   )    
  )

(defun my-cedet-keymap ()
    (local-set-key (kbd "RET") 'newline-and-indent)
)

(defun my-cedet-setup ()
	(require 'cedet)
	(my-cedet-setting)
	(my-cedet-keymap)
)

(defun my-cedet-launch ()
  (semantic-mode)
  (semanticdb-enable-cscope-databases)
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
  (require 'ecb-autoloads)
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
  (require 'cl-lib)
  (require 'eassist)
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
  (require 'ascope)
)
	
;; c mode.
(defun my-c-mode ()
  (interactive)
  (my-assist)	
  (my-cscope)
)

(add-hook 'c-mode-common-hook 
          '(lambda ()
             (my-c-mode)
             (run-with-idle-timer 0.01 nil 
                                  (lambda() 
                                    (mydev))
                                  ))
)

;; undo mode.
(defun my-undo ()
  (require 'undo-tree)
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
