const express = require('express');

const app = express();

app.set('view engine','ejs');

// localhost:3000
app.get('/', (req, res) => {
    res.render('home');
})

app.listen(3000, () => {
    console.log('port 3000');
})
