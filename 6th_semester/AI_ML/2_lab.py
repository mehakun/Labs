import nltk
from nltk.corpus import movie_reviews
from nltk.corpus import stopwords
from nltk.stem.porter import PorterStemmer

from sklearn.naive_bayes import MultinomialNB
from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import LogisticRegression

from sklearn.feature_extraction.text import CountVectorizer
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score


def apply_stemmer(text):
    res = []
    ps = PorterStemmer()

    for sent in text:
        words = sent.lower().split()
        stemmed_words = " ".join([ps.stem(word) for word in words if not word in set(stopwords.words('english'))])
        res.append(stemmed_words)

    return res


def main():
    nltk.download('stopwords')
    nltk.download('movie_reviews')
    
    neg_ids = movie_reviews.fileids('neg')
    pos_ids = movie_reviews.fileids('pos')
    neg_feats = [" ".join(movie_reviews.words(fileids=[f])) for f in neg_ids]
    pos_feats = [" ".join(movie_reviews.words(fileids=[f])) for f in pos_ids]

    reviews = apply_stemmer(neg_feats + pos_feats)

    labels = [0] * len(neg_feats) + [1] * len(pos_feats)

    X = CountVectorizer().fit_transform(reviews).toarray()

    X_train, X_test, y_train, y_test = train_test_split(X, labels, test_size=0.4, random_state=42)
    models = [[LogisticRegression(), "LogReg"], [KNeighborsClassifier(n_neighbors=5), "KNeighbors"], [MultinomialNB(), "MNB"]]

    for model in models:
        model[0].fit(X_train, y_train)
        y_pred = model[0].predict(X_test)
        model.append(accuracy_score(y_test, y_pred))

        print(f'{model[1]}: {model[-1]}')

# LogReg: 0.83125
# KNeighbors: 0.55625
# MNB: 0.80125

main()