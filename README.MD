# Exemples d'utilisation de clang

## Documentations
- Difference entre Matcher et Visitor : on voit bien que y'a moins de ligne de code pour le Matcher (on devrai detailler ça dans le rapport) : [ici](https://eli.thegreenplace.net/2014/07/29/ast-matchers-and-clang-refactoring-tools)
- Exemple de Matcher :[ici](https://github.com/thegameg/cast-matcher)
- Comment utiliser les ast Matcher (page 9) : [ici](https://docs.google.com/document/d/1oTkVLhCdRJUEH1_LDaQdXqe8-aOqT5GLDL9e4MhoFF8/edit#heading=h.sa6jil8n9n6w)
- définition de ce que c'est que LLVM (pour le rapport):[ici](https://www.scriptol.fr/programmation/llvm.php)
- Toutes les fonctions de l'ast Matcher:[ici](http://releases.llvm.org/3.5.0/tools/clang/docs/LibASTMatchersReference.html)

Apres chaque modification de code:

```
make
```

ASTMatcher:
```
cd /vagrant
build/clang_ast_matcher exemples/file.c -- -I/vagrant/libs/clang_llvm/lib/clang/3.9.1/include/
```