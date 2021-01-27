const express = require('express')
const app = express()
const port = 5000

const config = require('./config/key');
const bodyParser = require('body-parser');
const cookieParser = require('cookie-parser');
const { User } = require("./models/User");
const { auth } = require("./middleware/auth");

//! application/x-www-form-rulencoded
app.use(bodyParser.urlencoded({extended: true}));
//! application/json
app.use(bodyParser.json());

app.use(cookieParser());

const mongoose = require('mongoose');
const { request } = require('express');
mongoose.connect(config.mongoURI, {
    useNewUrlParser: true, useUnifiedTopology: true, useCreateIndex: true, useFindAndModify: false
}).then(() => console.log('MongoDB Connected...'))
.catch(err => console.log(err))

app.get('/', (req, res) => {
  res.send('Hello World! 12345')
})

app.post('/api/users/register', (req, res) => {
//!ȸ�� �����Ҷ� �ʿ��� �������� client���� �������� �װ͵��� �����ͺ��̽��� �־��ش�.
  const user = new User(req.body)

  user.save((err, doc) => {
    if(err) return res.json({success: false, err})
    return res.status(200).json({
      success: true
    })
  })
})

app.post('/api/users/login', (req, res) => {
  //! ��û�� �̸����� �����ͺ��̽����� �ִ��� Ȯ���Ѵ�.
  User.findOne({ email: req.body.email }, (err, user) => {
    if(!user){
      return res.json({
        loginSuccess: false,
        message: "������ �̸��Ͽ� �ش��ϴ� ������ �����ϴ�."
      })
    }
    //! �ִٸ� �̸��ϰ� ��й�ȣ�� ������ Ȯ���Ѵ�.
    user.comparePassword(req.body.password, (err, isMatch) => {
      if(!isMatch)
        return res.json({ loginSuccess: false, message: "��й�ȣ�� Ʋ�Ƚ��ϴ�."})

      //! ��й�ȣ�� �´ٸ� ��ū�� ����
      user.generateToken((err, user) => {
        if(err) return res.status(400).send(err);
        //!��ū�� �����Ѵ�. ���? ��Ű, ���ý��丮��
        res.cookie("x_auth", user.token)
        .status(200)
        .json({loginSuccess:true, userId: user._id})
      })
    })
  })
})

app.get('/api/users/auth', auth, (req, res) => {

  //!������� �̵��� ����� �Դٴ� ���� ������ ��� ��ٴ� ��
  res.status(200).json({
    _id: req.user._id,
    isAdmin: req.user.role === 0? false : true, //! 0�� �ƴϸ� ������
    isAuth:  true,
    email: req.user.email,
    name: req.user.name,
    lastname: req.user.lastname,
    role: req.user.role,
    image: req.user.image
  })
})

app.get('/api/users/logout', auth, (req, res) => {
  User.findOneAndUpdate({_id: req.user._id},
    {token: ""}
    , (err, user) =>{
      if (err) return res.json({success: false, err});
      return res.status(200).send({
        success: true
      })
    })
})


app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})