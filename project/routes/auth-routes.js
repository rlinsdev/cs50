// Enable to export routes
const router = require('express').Router();
const passport = require('passport');

// auth login
router.get('/login',(req, res) => {
    // Render login page
    res.render('login');
});

// auth logout
router.get('/logout', (req, res) => {
    // Log Out user
    req.logOut();
    // redirect to login page
    res.redirect('/');
})

router.get('/google', passport.authenticate('google', {
    scope: ['profile']
}));

// Must call authenticate again, because now we have google code access
router.get('/google/redirect', passport.authenticate('google'), (req, res) => {
    // Save user to profile page
    res.redirect('/profile');
})

module.exports = router;
