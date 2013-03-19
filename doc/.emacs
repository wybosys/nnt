;; common
(defun wybosys-absoulte-dir (path)
  (interactive)
  (directory-file-name (expand-file-name path)))

;; environment
(setq wybosys-home (wybosys-absoulte-dir (getenv "HOME")))
(setq wybosys-root (wybosys-absoulte-dir (getenv "ROOT")))
(setq wybosys-root-arch (wybosys-absoulte-dir (getenv "ROOT_ARCH")))
(setq wybosys-home "~/")
(setq wybosys-emacsd-home "~/.emacs.d/")
(setq wybosys-user-home wybosys-home)
(setq wybosys-lisp (concat wybosys-root "/share/emacs/site-lisp"))
(add-to-list 'load-path wybosys-lisp)
(setq wybosys-libexec-home (concat wybosys-root "/libexec"))
(setq wybosys-var-home (concat wybosys-root "/var"))
(setq wybosys-www-home (concat wybosys-root "/www"))
(setq wybosys-usr-home (concat wybosys-root "/usr"))
(setq wybosys-src-home (concat wybosys-root "/src"))
(setq wybosys-share-home (concat wybosys-root "/share"))
(setq wybosys-etc-home (concat wybosys-root "/ect"))
(setq wybosys-lib-home (concat wybosys-root "/lib"))

;; system set
(setq wybosys-script-custom nil)
(if (eq system-type 'windows-nt)
    (setq wybosys-script-custom t)
  )

(if (eq wybosys-script-custom t)
    (lambda() 
      (setq wybosys-python-home (wybosys-absoulte-dir (getenv "PYTHON_HOME")))
      (setq wybosys-perl-home (wybosys-absoulte-dir (getenv "PERL_HOME")))
      (setq wybosys-tcl-home (wybosys-absoulte-dir (getenv "TCL_HOME")))
      (setq wybosys-ruby-home (wybosys-absoulte-dir (getenv "RUBY_HOME")))
      )
  )

(prefer-coding-system 'utf-8)
(setq coding-system-for-read 'utf-8)
(setq coding-system-for-write 'utf-8)

(require 'info)
(add-to-list 'Info-directory-list (concat wybosys-share-home "/info"))

;; emacs
(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(blink-cursor-mode nil)
 '(c-basic-offset 4)
 '(column-number-mode t)
 '(ecb-auto-activate t)
 '(ecb-layout-name "wybosys-ecb-layout-prog")
 '(ecb-layout-window-sizes (quote (("wybosys-ecb-layout-prog" (0.2 . 0.2127659574468085) (0.2 . 0.46808510638297873) (0.2 . 0.2978723404255319)) ("wybosys-ecb-layout-simple" (0.2064516129032258 . 0.9787234042553191)) ("wybosys-ecb-layout-methods" (0.2129032258064516 . 0.9787234042553191)))))
 '(ecb-options-version "2.40")
 '(ecb-primary-secondary-mouse-buttons (quote mouse-1--mouse-2))
 '(ecb-tip-of-the-day nil)
 '(ecb-tree-buffer-style (quote ascii-guides))
 '(ecb-version-check nil)
 '(indent-tabs-mode nil)
 '(inhibit-startup-screen t)
 '(initial-scratch-message "")
 '(js2-indent-on-enter-key t)
 '(make-backup-files nil)
 '(scroll-bar-mode (quote right))
 '(session-use-package t nil (session))
 '(show-paren-mode t)
 '(smooth-scroll-margin 2)
 '(tab-width 4)
 '(tool-bar-mode nil))

;(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
; '(default ((t (:inherit nil :stipple nil :background "#102e4e" :foreground "#eeeeee" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 98 :width normal :foundry "outline" :family "Monaco"))))
; '(ecb-default-highlight-face ((((class color) (background dark)) (:background "royalblue")))))

;; font set
(if (eq system-type 'darwin)
    (custom-set-faces
     '(default ((t (:inherit nil :stipple nil :background "#102e4e" :foreground "#eeeeee" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 128 :width normal :foundry "outline" :family "Monaco"))))
     '(ecb-default-highlight-face ((((class color) (background dark)) (:background "royalblue")))))
  ; else
  (custom-set-faces
   '(default ((t (:inherit nil :stipple nil :background "#102e4e" :foreground "#eeeeee" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 98 :width normal :foundry "outline" :family "Monaco"))))
   '(ecb-default-highlight-face ((((class color) (background dark)) (:background "royalblue")))))
)    

;; font highlight
(global-font-lock-mode t)

;; load user config
(if (file-exists-p (concat wybosys-home "/.emacs.user"))
    (load-file (concat wybosys-home "/.emacs.user"))
)

;; ido mode
(ido-mode 1)
(require 'template-simple)
(add-to-list 'ido-ignore-files "\\.DS_Store")

;; session
(require 'session)
(add-hook 'after-init-hook 'session-initialize)
(require 'desktop)
(desktop-load-default)
(add-to-list 'desktop-path wybosys-emacsd-home)

;; uniquify buffer name
(require 'uniquify)
(setq uniquify-buffer-name-style 'reverse)

;; emacs settings
;(menu-bar-left-scroll-bar)
(global-auto-revert-mode t)

;; elib
(add-to-list 'load-path (concat wybosys-lisp "/elib"))
(require 'string)

;; load wybosys
(require 'wybosys)

;; color-theme
(add-to-list 'load-path (concat wybosys-lisp "/color-theme"))
(require 'color-theme)
(color-theme-initialize)

;; saveplace
;(require 'saveplace)
;(setq-default save-place t)

;; auto-complete
(add-to-list 'load-path (concat wybosys-lisp "/auto-complete"))
;(require 'auto-complete-config)'
;(add-to-list 'ac-dictionary-directories (concat wybosys-lisp "/auto-complete/ac-dict"))
;(ac-config-default)

;; highlight current line
(require 'highlight-current-line)
(highlight-current-line-on t)
;(highlight-current-line-set-bg-color "#dcdcdc")
(highlight-current-line-set-bg-color "#000000")

;; cscope
(require 'xcscope)

;; cedet
(add-to-list 'load-path (concat wybosys-lisp "/cedet"))
(add-to-list 'load-path (concat wybosys-lisp "/cedet/common"))
(require 'cedet)
;(semantic-load-enable-minimum-features)
(semantic-load-enable-code-helpers)
;(semantic-load-enable-guady-code-helpers)
;(semantic-load-enable-excessive-code-helpers)
;(semantic-load-enable-semantic-debugging-helpers)

;; cedet folding function
(global-semantic-tag-folding-mode 1)

;; cedet for c like language
(defun wybosys-cedet-hook-c()
  (local-set-key [(control return)] 'semantic-ia-complete-symbol)
  (local-set-key "\M-/" 'semantic-ia-complete-symbol-menu)
  (local-set-key "\C-c>" 'semantic-complete-analyze-inline)
  (local-set-key "\C-cp" 'semantic-analyze-proto-impl-toggle)
  (local-set-key "." 'semantic-complete-self-insert)
  (local-set-key ">" 'semantic-complete-self-insert)
)
(add-hook 'c-mode-common-hook 'wybosys-cedet-hook-c)
;; cedet for lisp
(defun wybosys-cedet-hook-el()
  (local-set-key [(control return)] 'semantic-ia-complete-symbol)
  (local-set-key "\M-/" 'semantic-ia-complete-symbol-menu)
  (local-set-key "\C-c>" 'semantic-complete-analyze-inline)
  (local-set-key "\C-cp" 'semantic-analyze-proto-impl-toggle)
)
(add-hook 'lisp-mode-hook 'wybosys-cedet-hook-el)
(add-hook 'emacs-lisp-mode-hook 'wybosys-cedet-hook-el)
;; cedet for js2
(defun wybosys-cedet-js-indent-or-complete()
  (interactive)
  (if (looking-at "\\.")
      (dabbrev-expand)
    (indent-for-tab-command))
)
(defun wybosys-cedet-hook-js()
  (local-set-key "\M-[" 'find-tag)
  ;(local-set-key [(tab)] 'wybosys-cedet-js-indent-or-complete)
)
(add-hook 'js2-mode-hook 'wybosys-cedet-hook-js)

;; ecb
(add-to-list 'load-path (concat wybosys-lisp "/ecb"))
;(require 'ecb)
(require 'ecb-autoloads)
(setq wybosys-ecb-actived nil)
(defun wybosys-ecb-active()
  (setq wybosys-ecb-actived t)
  (wybosys-maximize-frame)
  (sit-for 0.1)
  (ecb-activate)
  (setq default-directory wybosys-user-home)
)
(defun wybosys-ecb-deactive()
  (setq wybosys-ecb-actived nil)
  (ecb-deactivate)
  (sit-for 0.1)
  (wybosys-restore-frame)
)
(defun wybosys-ecb-toggle-active()
  (interactive)
  (if (equal wybosys-ecb-actived nil)
      (wybosys-ecb-active)
    (wybosys-ecb-deactive))
)
(global-set-key (kbd "<f2> <f5>") 'wybosys-ecb-toggle-active)
(add-hook 'ecb-before-activate-hook 'wybosys-ecb-init)
(defun wybosys-ecb-on-activate()
  ;(ecb-hide-ecb-windows)
  ;(global-set-key (kbd "<f11>") 'ecb-toggle-ecb-windows)
)
(add-hook 'ecb-activate-hook 'wybosys-ecb-on-activate)

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
      verilog-linter			 "my_lint_shell_command"
      )

;; javascript
(require 'js2-mode)
;(autoload 'js2-mode "js2" nil t)
(setq auto-mode-alist (cons '("\\.js$" . js2-mode) auto-mode-alist))
(setq auto-mode-alist (cons '("\\.json$" . js2-mode) auto-mode-alist))
(add-hook 'js2-mode-hook (lambda ()
                           ;(yas/activate)
                           ))

;; qooxdoo
(require 'qx-mode)

;; php-mode
(require 'php-mode)
(setq auto-mode-alist (cons '("\\.php$" . php-mode) auto-mode-alist))
(defun drupal-mode ()
  (interactive)
  (setq auto-mode-alist (cons '("\\.module$" . php-mode) auto-mode-alist))
  (setq auto-mode-alist (cons '("\\.install$" . php-mode) auto-mode-alist))
  (message "Start Drupal-Mode")
)

;; erlang
(add-to-list 'load-path (concat wybosys-lisp "/erlang"))
(require 'erlang-start)

;; scala
(add-to-list 'load-path (concat wybosys-lisp "/scala"))
(require 'scala-mode-auto)

;; haskell
(add-to-list 'load-path (concat wybosys-lisp "/haskell"))
(load-file (concat wybosys-lisp "/haskell/haskell-site-file.el"))
(add-hook 'haskell-mode-hook 'turn-on-haskell-doc-mode)
(add-hook 'haskell-mode-hook 'turn-on-haskell-indentation)
;;(add-hook 'haskell-mode-hook 'turn-on-haskell-indent)
;;(add-hook 'haskell-mode-hook 'turn-on-haskell-simple-indent)

;; version control managment
(add-to-list 'load-path (concat wybosys-lisp "/vcm"))
(require 'git)
;(require 'git-blame)
(require 'git-emacs)
;(require 'vc-svn)

;; smooth scroll
(require 'smooth-scrolling)

;; smart tabs
;(require 'smarttabs)
;(smart-tabs-advice js2-indent-line js2-basic-offset)

;; sinppet
;; yasinppets
(add-to-list 'load-path (concat wybosys-lisp "/yasnippet"))
(setq yas/isactivated nil)
(defun yas/activate ()
  (interactive)
  (if (eq yas/isactivated nil)
      (progn
        (message "Loading yasnippets ...")
        (require 'yasnippet)
        (yas/initialize)
        (yas/load-directory (concat wybosys-lisp "/yasnippet/snippets"))
        (require 'dropdown-list)
        (setq yas/prompt-functions '(yas/dropdown-prompt
                                     yas/ido-prompt
                                     yas/completing-prompt))
        (setq yas/isactivated t)
        )
  ))
                             
;; org-mode
(add-to-list 'load-path (concat wybosys-lisp "/org"))
(add-to-list 'load-path (concat wybosys-lisp "/org/lisp"))
(require 'org-install)
(require 'org-publish)
(add-to-list 'auto-mode-alist '("\\.org\\'" . org-mode))

;; company-mode
(add-to-list 'load-path (concat wybosys-lisp "/company-mode"))
(autoload 'company-mode "company" nil t)

;; aspell
(setq-default ispell-program-name "aspell-nocurse")
(let ((wybosysargs ()))
  (setq aspell-dict-dir (concat wybosys-root "/share/aspell/dict"))
  (setq aspell-data-dir (concat wybosys-root "/share/aspell/data"))
  (add-to-list 'wybosysargs "--reverse")
  (add-to-list 'wybosysargs (concat "--data-dir=" aspell-data-dir))
  (add-to-list 'wybosysargs (concat "--dict-dir=" aspell-dict-dir))
  (add-to-list 'wybosysargs "--lang=en")
  (setq-default ispell-extra-args wybosysargs)
)

;; mew
(add-to-list 'load-path (concat wybosys-lisp "/mew"))
(autoload 'mew "mew" nil t)
(autoload 'mew-send "mew" nil t)

(setq mew-prog-ssl "stunnel")
;(setq mew-prog-ssl-arg (concat wybosys-root "etc/stunnel/stunnel.conf"))
(setq mew-summary-for '(type (5 data) " " (14 form) " " t (30 subj) "|" (0 body)))
(setq mew-summary-form-extract-rule '(name))

; setup
(setq mew-mail-path "~/.mail")
(if (file-exists-p "~/.mail.wybosys")
		(load-file "~/.mail.wybosys"))
(setq mew-user-cached-passwd t)

; Optional setup (Read Mail menu for Emacs 21):
(if (boundp 'read-mail-command)
    (setq read-mail-command 'mew))

; Optional setup (e.g. C-xm for sending a message):
(autoload 'mew-user-agent-compose "mew" nil t)
(if (boundp 'mail-user-agent)
    (setq mail-user-agent 'mew-user-agent))
(if (fboundp 'define-mail-user-agent)
    (define-mail-user-agent
      'mew-user-agent
      'mew-user-agent-compose
      'mew-draft-send-message
      'mew-draft-kill
      'mew-send-hook))

;; doxymacs
(add-to-list 'load-path (concat wybosys-lisp "/w3/lisp"))
(add-to-list 'load-path (concat wybosys-lisp "/doxymacs"))
(setq doxymacs-isloaded nil)
(add-hook 'c-mode-common-hook (lambda () 
                                (if (eq doxymacs-isloaded nil)
                                    (progn
                                      (require 'doxymacs)
                                      (setq doxymacs-isloaded t)))
                                (doxymacs-mode)
                                ))

;; perl
(defalias 'perl-mode 'cperl-mode)
(add-to-list 'auto-mode-alist '("\\.\\([pP][Llm]\\|al\\)\\'" . cperl-mode))
(add-to-list 'interpreter-mode-alist '("perl" . cperl-mode))
(add-to-list 'interpreter-mode-alist '("perl5" . cperl-mode))
(add-to-list 'interpreter-mode-alist '("miniperl" . cperl-mode))
(add-hook 'cperl-mode-hook (lambda () 
                             (require 'perl-find-library)
                             (require 'wybosys-perl-find-library-cache)
                             (if (eq wybosys-script-custom t)
                                 (lambda ()
                                   (add-to-list '*perl-lib-path* (concat wybosys-perl-home "/lib"))
                                   (setq *wybosys-perl-cache-libraries-dir* (concat wybosys-var-home "/cache/perl/lib"))  
                                   ))
                             ))

;; latex
; auctex
(add-to-list 'load-path (concat wybosys-lisp "/auctex"))
(add-to-list 'load-path (concat wybosys-lisp "/auctex/site-lisp"))
(add-to-list 'load-path (concat wybosys-lisp "/auctex/site-lisp/auctex"))
(add-to-list 'load-path (concat wybosys-lisp "/auctex/site-lisp/site-start.d"))
(require 'tex-site)
(require 'tex-mik)
(autoload 'latex-mode "latex-mode" "Auctex mode" t)
(add-to-list 'auto-mode-alist '("\\.tex[i]?\\'" . latex-mode))
(add-hook 'LaTeX-mode-hook
          (lambda ()
            (setq TeX-auto-untabify t     ; remove all tabs before saving
                  TeX-engine 'xetex       ; use xelatex default
                  TeX-show-compilation nil ; display compilation windows
                  TeX-save-query  nil     ; no prompt for saving
                  )
            (TeX-global-PDF-mode t)       ; PDF mode enable, not plain
            (setq TeX-save-query nil)
            (imenu-add-menubar-index)
            ;(define-key LaTeX-mode-map (kbd "TAB") 'TeX-complete-symbol)
            ))
(cond
 ((eq system-type 'windows-nt)
  (add-hook 'LaTeX-mode-hook
            (lambda ()
              (setq TeX-view-program-list
                    '(
                      ("SumatraPDF"   "SumatraPDF.exe %o")
                      ("Gsview"       "gsview32.exe %o")
                      ("Yap"          "yap.exe %o")
                      ))
              (setq TeX-view-program-selection '(
                                                 (output-pdf "SumatraPDF")
                                                 (output-dvi "Yap"))
                    )
              )
            )
  ))
; ultratex
;(add-to-list 'load-path (concat wybosys-lisp "/ultratex/lisp"))

;; highlight-tails
;(setq highlight-tail-colors
;          '(("black" . 0)
;            ("#bc2525" . 25)
;            ("black" . 66)))

;; pretty line break
(require 'pp-c-l)
(pretty-control-l-mode 1)

;; pulse
(require 'pulse)
;(pulse-toggle-integration-advice (if window-system 1 -1))

;; script debug
; genben-on-emacs
(add-to-list 'load-path (concat wybosys-lisp "/geben"))
(require 'geben)

;; anything
(add-to-list 'load-path (concat wybosys-lisp "/anything"))
(add-to-list 'load-path (concat wybosys-lisp "/anything/extensions"))
;(require 'anything-startup)
;(require 'anything-config)

;; tramp
;(add-to-list 'load-path (concat wybosys-lisp "/tramp"))
(add-to-list 'load-path (concat wybosys-lisp "/tramp/lisp"))
;(add-to-list 'Info-directory-list (concat wybosys-share-home "/info/"))
(require 'tramp)
(if (eq system-type 'windows-nt)
    (setq tramp-default-method "plink")
  (setq tramp-default-method "ssh")
)

;; bookmark+
(add-to-list 'load-path (concat wybosys-lisp "/bookmark+"))
(require 'bookmark+)

;; icicles
(add-to-list 'load-path (concat wybosys-lisp "/icicles"))

;; xlst-process
(add-to-list 'load-path (concat wybosys-lisp "/xslt-process/lisp"))
(autoload 'xslt-process-mode "xslt-process" "Emacs XSLT processing" t)
(autoload 'xslt-process-install-docbook "xslt-process"
  "Register the DocBook package with XSLT-process" t)
(defun wybosys-xslt-process-mode () 
  (xslt-process-mode 1)
  (toggle-read-only 0)
  )
;(add-hook 'sgml-mode-hook 'wybosys-xslt-process-mode)
;(add-hook 'xml-mode-hook 'wybosys-xslt-process-mode)
;(add-hook 'xsl-mode-hook 'wybosys-xslt-process-mode)
(defadvice xml-mode (after run-xml-mode-hooks act)
  "Invoke `xml-mode-hook' hooks in the XML mode."
  (run-hooks 'xml-mode-hook))

;; psgml
(add-to-list 'load-path (concat wybosys-lisp "/psgml"))
;(require 'psgml)

;; mmm-mode
(add-to-list 'load-path (concat wybosys-lisp "/mmm-mode"))
;(require 'mmm-mode)
; delux mode
;(setq mmm-global-mode 'maybe)
;(mmm-add-group
; 'php-in-html
; '(
;   (html-php-tagged
;    :submode php-mode
;    :front "<\?"
;    :back "\?>"
;    :include-back t)))
;(add-hook 'html-mode-hook '(lambda ()
;                             (setq mmm-classes '(php-in-html))
;                             (set-face-background
;                              'mmm-default-submode-face "Blank")
;                             (mmm-mode-on)))
;(add-to-list 'auto-mode-alist '("\\.php$" . html-mode))
;(add-to-list 'mmm-mode-ext-classes-alist '(html-mode nil fancy-html))

;; hideshow
(load-library "hideshow")
(add-hook 'php-mode-hook 'hs-minor-mode)

;; win32
(if (eq system-type 'windows-nt)
    (progn
      (add-to-list 'load-path (concat wybosys-lisp "/win32"))
                                        ;(require 'w32-fullscreen)
      ))

;; dictd
(add-to-list 'load-path (concat wybosys-lisp "/dictionary"))
(require 'dictionary)
(setq dictionary-coding-systems-for-dictionaries '(("cdict" . gb2312)
                                                   ("xdict" . gbk2312)
                                                  ("stardic" . gb2312)))  

;; buffer
(global-set-key (kbd "C-x C-<up>") 'switch-to-buffer)
(global-set-key (kbd "C-<tab>") 'switch-to-buffer)
(global-set-key (kbd "C-x C-<down>") 'other-window)
(global-set-key (kbd "<mouse-1>") 'mouse-set-point)
(global-set-key (kbd "<down-mouse-1>") 'mouse-drag-region)
(global-set-key (kbd "C-<down>") 'next-logical-line)
(global-set-key (kbd "C-<up>") 'previous-logical-line)
(global-set-key (kbd "M-<down>") 'forward-paragraph)
(global-set-key (kbd "M-<up>") 'backward-paragraph)
(global-set-key (kbd "<end>") 'bookmark-set)
(global-set-key (kbd "<home>") 'bookmark-jump)
;(global-set-key (kbd "<f11>") 'w32-fullscreen)
(global-set-key (kbd "<f11>") 'wybosys-maximize-frame)

;; other
;(wybosys-w32-maximize-frame)
(color-theme-wybo)
(setq other-window-scroll-buffer t)

;; font
(set-fontset-font (frame-parameter nil 'font) 
                  'han (font-spec :family "SimSun"))
      
(if (eq system-type 'windows-nt)
    (progn
      (setq default-frame-alist 
	    '((height . 30) 
	      (width . 100)
	      (top . 150)
	      (left . 200)
	      ))
      ))

;; reset
(setq default-directory wybosys-user-home)