const express = require('express');
const authRoutes = require('./routes/auth-routes');
const passportSetup = require('./config/passport-setup');
const mongoose = require('mongoose');
const keys = require('./config/keys');

const app = express();

// View Engine
app.set('view engine','ejs');

// Mongo
mongoose.set('strictQuery', true);
mongoose.connect(keys.mongodb.dbURI, () => {
    console.log('Mongo connected');
});

// Point to routes in folder
app.use('/auth', authRoutes);

// localhost:3000
app.get('/', (req, res) => {
    res.render('home');
})

app.listen(3000, () => {
    console.log('link: http://localhost:3000');
})
