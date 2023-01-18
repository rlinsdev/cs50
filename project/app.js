const express = require('express');
const authRoutes = require('./routes/auth-routes');
const profileRoutes = require('./routes/profile-routes');
const passportSetup = require('./config/passport-setup');
const mongoose = require('mongoose');
const keys = require('./config/keys');
const cookieSession = require('cookie-session');
const passport = require('passport');

const app = express();

// View Engine
app.set('view engine','ejs');

app.use(cookieSession({
    maxAge: 24 * 60 * 60 * 1000,  // Expiration = 1 day
    keys:[keys.session.cookieKey]
}));

// Initialize passport
app.use(passport.initialize());
// Initialize session cookie
app.use(passport.session());

// Mongo
mongoose.set('strictQuery', true);
mongoose.connect(keys.mongodb.dbURI, () => {
    console.log('Mongo connected');
});

// Point to routes in folder
app.use('/auth', authRoutes);
app.use('/profile', profileRoutes);

// localhost:3000
app.get('/', (req, res) => {
    res.render('home');
})

app.listen(3000, () => {
    console.log('link: http://localhost:3000');
})
