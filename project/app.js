const express = require('express');
const authRoutes = require('./routes/auth-routes');
const passportSetup = require('./config/passport-setup');

const app = express();

app.set('view engine','ejs');

// Point to routes in folder
app.use('/auth', authRoutes);

// localhost:3000
app.get('/', (req, res) => {
    res.render('home');
})

app.listen(3000, () => {
    console.log('link: http://localhost:3000');
})
