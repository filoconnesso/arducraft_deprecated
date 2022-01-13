import React from "react";
import Head from "next/head";
import Link from "next/link";

import {
  Layout,
  Form,
  Select,
  InputNumber,
  DatePicker,
  Switch,
  Slider,
  Input,
  PageHeader,
} from "antd";

const { Header, Content } = Layout;
const { Item: FormItem } = Form;
const { Option } = Select;

//StartBot(serial_port, hostname, port, version, bot_name)

function Home() {
  return (
    <body style={{}}>
      <React.Fragment>
        <Head>
          <title>Arducraft-GUI</title>
        </Head>
        <PageHeader
          className="site-page-header"
          title="Arducraft-GUI"
          style={{ borderBottom: "5px solid #26547C" }}
        />
        <Content style={{ marginTop: 50 }}>
          <Form layout="horizontal">
            <FormItem
              label="Serial Port"
              labelCol={{ span: 4 }}
              wrapperCol={{ span: 8 }}
            >
              <Select size="large" defaultValue="sp2" style={{ width: 192 }}>
                <Option value="sp1">jack</Option>
                <Option value="sp2">lucy</Option>
                <Option value="disabled" disabled>
                  disabled
                </Option>
                <Option value="sp3">yiminghe</Option>
              </Select>
            </FormItem>
            <FormItem
              label="Domain Name"
              labelCol={{ span: 4 }}
              wrapperCol={{ span: 8 }}
            >
              <Input
                size="large"
                style={{ width: 100 }}
                defaultValue= "localhost"
                name="hostname"
              />
            </FormItem>

            <FormItem
              label="Port Number"
              labelCol={{ span: 4 }}
              wrapperCol={{ span: 8 }}
            >
              <InputNumber
                size="large"
                min={1}
                max={10}
                style={{ width: 100 }}
                defaultValue={3}
                name="inputNumber"
              />
            </FormItem>

            <FormItem
              label="Server Version"
              labelCol={{ span: 4 }}
              wrapperCol={{ span: 8 }}
            >
              <Input
                size="large"
                style={{ width: 100 }}
                defaultValue={3}
                name="hostname"
              />
            </FormItem>

            <FormItem
              label="Bot Name"
              labelCol={{ span: 4 }}
              wrapperCol={{ span: 8 }}
            >
              <Input
                size="large"
                style={{ width: 100 }}
                defaultValue={3}
                name="hostname"
              />
            </FormItem>

            <FormItem
              label="Bot State"
              labelCol={{ span: 4 }}
              wrapperCol={{ span: 8 }}
            >
              <Switch defaultChecked />
            </FormItem>
          </Form>
        </Content>
      </React.Fragment>
    </body>
  );
}

export default Home;
