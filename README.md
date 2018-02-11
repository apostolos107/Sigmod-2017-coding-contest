# Project
Our solution for the SIGMOD 2017 contest problem. This project has been implemented within the 2017 winter semester.
We are students at National And Kapodistrian University of Athens at Department Of Informatics and Telecommunications.

# Contributors

## Ilias Mentzelos
## Apostolos Plakias
## Athanasios Poludoros

# What is it?
( More on http://sigmod17contest.athenarc.gr/ )

An N-gram of words is a contiguous sequence of N words (https://en.wikipedia.org/wiki/N-gram). For this year's contest, the task is to filter a stream of documents using a set of N-grams of interest and, for each document, return where in it one of the N-grams is found The input to the task will have two parts: first, an initial set of N-grams, which may be processed and indexed; second, a series of queries (documents) and N-gram updates (insertions or deletions), arbitrarily interleaved. For each N-gram insertion or deletion, the set of N-grams of interest is updated accordingly. For each new query (document) arriving, the task is to return as fast as possible the N-grams of the currently up-to-date set that are found in the document. These should be presented in order of their first appearance in the document. If one N-gram is a prefix of another and the larger one is in the document, then the shorter one is presented first
