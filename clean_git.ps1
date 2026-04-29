git update-ref -d HEAD
git rm -r --cached .
git add .
git commit -m "fix: purgar binarios y librerías pesadas del historial"
git push -f origin main
