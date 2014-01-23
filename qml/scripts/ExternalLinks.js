.pragma library

function browse(url)
{
    Qt.openUrlExternally(url)
}

function mail(email, subject)
{
    Qt.openUrlExternally("mailto:"+email+"?subject="+subject)
}

function searchGoogle(terms)
{
    var parameters = [];
    for (var i = 0; i < terms.length; i++) {
        parameters.push(encodeURIComponent(terms[i]))
    }

    var url = "http://www.google.com/search?q="+parameters.join('+')
    Qt.openUrlExternally(url)
}
