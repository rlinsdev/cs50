// Enable to export routes
const router = require('express').Router();

// auth login
router.get('/login',(req, res) => {
    res.render('login');
});

// auth logout
router.get('/logout', (req, res) =>{
    res.send("log out with passport");
})

// google
router.get('/google', (req, res) => {
    res.send("login google with passport");
});

module.exports = router;
