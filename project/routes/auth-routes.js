// Enable to export routes
const router = require('express').Router();
const passport = require('passport');

// auth login
router.get('/login',(req, res) => {
    res.render('login');
});

// auth logout
router.get('/logout', (req, res) =>{
    res.send("log out with passport");
})

// google
router.get('/google', passport.authenticate('google', {
    scope: ['profile']
}));

module.exports = router;
